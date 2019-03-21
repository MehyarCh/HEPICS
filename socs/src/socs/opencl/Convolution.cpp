#include "Convolution.h"
#include "Paths.h"
#include <cstring>
#include <fstream>

namespace socs {
namespace opencl {

using namespace std;

constexpr auto altera_platform_name = "Altera SDK for OpenCL";
constexpr auto de1soc_device_name = "de1soc_sharedonlyCyclone V SoC Development Kit";
constexpr auto opencl_kernel_name = "convolution";

constexpr size_t block_size = 64 * 16;

static auto make_parameters() {
	using Parameters = Convolution::Parameters;
	return vector<shared_ptr<const Parameters>> {
			make_shared<Parameters>(make_unique<Blob>(11, 11, 3, 96),
					Paths::data_path + "convolutional_layer_0_weights"s,
					vector<float>(96),
					Paths::data_path + "convolutional_layer_0_bias_vector"s,
					4, 0, 1),
			make_shared<Parameters>(make_unique<Blob>(5, 5, 48, 256),
					Paths::data_path + "convolutional_layer_1_weights"s,
					vector<float>(256),
					Paths::data_path + "convolutional_layer_1_bias_vector"s,
					1, 2, 2),
			make_shared<Parameters>(make_unique<Blob>(3, 3, 256, 384),
					Paths::data_path + "convolutional_layer_2_weights"s,
					vector<float>(384),
					Paths::data_path + "convolutional_layer_2_bias_vector"s,
					1, 1, 1),
			make_shared<Parameters>(make_unique<Blob>(3, 3, 192, 384),
					Paths::data_path + "convolutional_layer_3_weights"s,
					vector<float>(384),
					Paths::data_path + "convolutional_layer_3_bias_vector"s,
					1, 1, 2),
			make_shared<Parameters>(make_unique<Blob>(3, 3, 192, 256),
					Paths::data_path + "convolutional_layer_4_weights"s,
					vector<float>(256),
					Paths::data_path + "convolutional_layer_4_bias_vector"s,
					1, 1, 2),
	};
}

Convolution Convolution::make() {
	auto is_altera = [](const string &name) {return name == altera_platform_name;};
	auto is_de1soc = [](const string &name) {return name == de1soc_device_name;};

	auto platform = Platform { is_altera };
	auto device = Device { is_de1soc, platform };
	auto context = make_shared<Context>(platform, device);
	auto program = is_altera(platform.get_name()) ? make_shared<Program>(string(Paths::aocx_path), *context, device) :
													make_shared<Program>(string(Paths::cl_path), *context);
	program->build(device);
	auto opencl_kernel = make_shared<Kernel>(*program, opencl_kernel_name);
	auto queue = make_shared<Command_queue>(*context, device, false);

	return Convolution { platform, device, context, move(program), opencl_kernel, queue, make_parameters() };
}

static void ensure_valid_param_index(size_t param_index,
		const vector<shared_ptr<const Convolution::Parameters>> &params) {
	if (param_index >= params.size()) {
		throw Invalid_param_index { };
	}
}

static void ensure_valid_input(const Blob &input, const Blob &filters, size_t groups) {
	if (input.channels != groups * filters.channels || input.num != 1) {
		throw Invalid_input { };
	}
}

class Sliced_filters {
public:
	using Filter = vector<unique_ptr<Buffer>>;

	Sliced_filters(const Blob &filters, const Context &context, const Command_queue &queue);

	const vector<Filter> filters;
	const size_t filter_size;
};

static auto get_filter_size(const Blob &filters) {
	return filters.width * filters.height * filters.channels;
}

static auto make_sliced_filters(const Blob &filters, const Context &context, const Command_queue &queue) {
	auto filter_size = get_filter_size(filters);
	auto num_blocks = (get_filter_size(filters) - 1) / block_size + 1;
	auto out = vector<Sliced_filters::Filter> { };
	auto wait_list = vector<cl_event> { };
	auto events = vector<unique_ptr<Event>> { };
	for (size_t j = 0; j < filters.num; ++j) {
		auto filter = &filters.at(0, 0, 0, j);
		auto sliced = Sliced_filters::Filter { };
		for (size_t i = 0; i < num_blocks; ++i) {
			auto pos = i * block_size;
			auto rem_size = filter_size - pos;
			auto block = make_unique<Buffer>(block_size * sizeof(float), CL_MEM_READ_ONLY, context);
			auto s = min(rem_size, block_size) * sizeof(float);
			memcpy(block->mem.array, filter + pos, s);
			memset(block->mem.array + s, 0, block->mem.length - s);
			auto event = queue.queue_write(*block);
			sliced.push_back(move(block));
			wait_list.push_back(event->event);
			events.push_back(move(event));
		}
		out.push_back(move(sliced));
	}
	Event::wait(wait_list);
	return out;
}

Sliced_filters::Sliced_filters(const Blob &filters, const Context &context, const Command_queue &queue) :
		filters { make_sliced_filters(filters, context, queue) }, filter_size { get_filter_size(filters) } {
}

static auto get_input_value(const Blob &input, size_t x, size_t y, size_t c) {
	return x < input.width && y < input.height && c < input.channels ? input.at(x, y, c, 0) : 0;
}

class Data_sink {
public:
	using Buffer = vector<unique_ptr<opencl::Buffer>>;

	Data_sink(size_t buf_vec_size, size_t num_dpd, const Sliced_filters &filters, const vector<float> &bias_vec,
			const Kernel &kernel, const Command_queue &queue, const Context &context);
	void set_flt_idx(size_t flt_idx);
	void write_value(float value);
	void end_dot_prod();
	void end_filter();
	void end_convolution();
	unique_ptr<Blob> make_result_blob(size_t width, size_t height, size_t channels);

private:
	void queue_data();

	vector<Buffer> buf_vec;
	vector<unique_ptr<Event>> evt_vec;
	size_t num_dpd;
	size_t flt_idx;
	size_t buf_idx;
	size_t dpd_idx;
	size_t slc_idx;
	size_t val_idx;
	const Sliced_filters &filters;
	const vector<float> &bias_vec;
	const Kernel &kernel;
	const Command_queue &queue;
	const Context &context;
	Buffer result;

};

static auto make_buf_vec(size_t buf_vec_size, size_t num_dpd, const Sliced_filters &filters, const Context &context) {
	auto buf_vec = vector<Data_sink::Buffer> { };
	for (size_t j = 0; j < buf_vec_size; ++j) {
		auto buffer = Data_sink::Buffer { };
		for (size_t i = 0, n = filters.filters[0].size(); i < n; ++i) {
			buffer.push_back(
					make_unique<Buffer>(num_dpd * block_size * sizeof(float), CL_MEM_READ_ONLY, context));
		}
		buf_vec.push_back(move(buffer));
	}
	return buf_vec;
}

Data_sink::Data_sink(size_t buf_vec_size, size_t num_dpd, const Sliced_filters &filters, const vector<float> &bias_vec,
		const Kernel &kernel, const Command_queue &queue, const Context &context) :
		buf_vec(make_buf_vec(buf_vec_size, num_dpd, filters, context)), evt_vec(buf_vec_size),
				num_dpd { num_dpd }, flt_idx { 0 }, buf_idx { 0 }, dpd_idx { 0 }, slc_idx { 0 }, val_idx { 0 },
				filters { filters }, bias_vec { bias_vec }, kernel { kernel }, queue { queue }, context { context }, result { } {
}

static auto loop_inc(size_t idx, size_t size) {
	return (idx + 1) % size;
}

void Data_sink::set_flt_idx(size_t flt_idx) {
	this->flt_idx = flt_idx;
}

void Data_sink::write_value(float value) {
	auto &buffer = buf_vec[buf_idx];
	auto &slice = *buffer[slc_idx];
	auto payload = min((filters.filter_size + (16-1)) / 16 * 16 - slc_idx * block_size, block_size);
	reinterpret_cast<float *>(slice.mem.array)[dpd_idx * payload + val_idx] = value;
	val_idx = loop_inc(val_idx, payload);
	if (val_idx == 0) {
		++slc_idx;
	}
}

static void wait_for(const Event *event) {
	if (event != nullptr) {
		Event::wait(vector<cl_event> { event->event });
	}
}

void Data_sink::end_dot_prod() {
	while (val_idx % 16 != 0) {
		write_value(0.0f);
	}
	val_idx = 0;
	slc_idx = 0;
	dpd_idx = loop_inc(dpd_idx, num_dpd);

	if (dpd_idx == 0) {
		queue_data();
		buf_idx = loop_inc(buf_idx, buf_vec.size());
		wait_for(evt_vec[buf_idx].get());
	}
}

void Data_sink::end_filter() {
	if (dpd_idx != 0) {
		queue_data();
		dpd_idx = 0;
		buf_idx = loop_inc(buf_idx, buf_vec.size());
		wait_for(evt_vec[buf_idx].get());
	}
}

void Data_sink::end_convolution() {
	for (auto &event : evt_vec) {
		wait_for(event.get());
	}
}

void Data_sink::queue_data() {
	auto dpd_count = dpd_idx == 0 ? num_dpd : dpd_idx;
	auto &buffer = buf_vec[buf_idx];
	auto &filter = filters.filters[flt_idx];
	auto bias = bias_vec[flt_idx];

	auto conv_res = make_unique<opencl::Buffer>(dpd_count * sizeof(float), CL_MEM_READ_WRITE, context);
	auto a = reinterpret_cast<float *>(conv_res->mem.array);
	for (size_t i = 0; i < dpd_count; ++i) {
		a[i] = bias;
	}
	auto event = queue.queue_write(*conv_res);

	for (size_t i = 0, n = buffer.size(); i < n; ++i) {
		auto buf_slice = buffer[i].get();
		auto payload = min((filters.filter_size + (16-1)) / 16 * 16 - i * block_size, block_size);
		auto dat_evt = queue.queue_write(*buf_slice, vector<cl_event> { }, dpd_count * payload * sizeof(float));

		auto flt_slice = filter[i].get();
		auto reduction_size = (payload + (16 - 1)) / 16;

		auto x = (float *)buf_slice->mem.array;
		auto y = (float *)flt_slice->mem.array;

		kernel.set_arg(0, *buf_slice);
		kernel.set_arg(1, *flt_slice);
		kernel.set_arg(2, *conv_res);
		kernel.set_arg(3, reduction_size);

		auto work_size = vector<size_t> { dpd_count * 64, 1, 1 };
		auto local_size = vector<size_t> { 64, 1, 1 };
		auto wait_list = vector<cl_event> { dat_evt->event, event->event };

		event = queue.queue_kernel(kernel, work_size, local_size, wait_list);
	}

	evt_vec[buf_idx] = queue.queue_read(*conv_res, vector<cl_event> { event->event });
	auto z = (float *)conv_res->mem.array;;
	result.push_back(move(conv_res));
}

unique_ptr<Blob> Data_sink::make_result_blob(size_t width, size_t height, size_t channels) {
	auto out = make_unique<Blob>(width, height, channels, 1);
	auto p = out->ptr();
	auto s = out->size() * sizeof(float);
	for(auto &res_block : result) {
		auto cs = min(s, res_block->mem.length);
		memcpy(p, res_block->mem.array, cs);
		p += cs / sizeof(float);
	}
	return move(out);
}

unique_ptr<Blob> Convolution::run(size_t param_index, const Blob &input) const {
	ensure_valid_param_index(param_index, params);
	auto &p = *params[param_index];
	ensure_valid_input(input, *p.filters, p.groups);

	auto sliced = make_unique<Sliced_filters>(*p.filters, *context, *queue);
	auto sink = make_unique<Data_sink>(3, 1024, *sliced, p.bias_vec, *opencl_kernel, *queue, *context);

	auto out_width = (input.width + 2 * p.pad - p.filters->width) / p.stride + 1;
	auto out_height = (input.height + 2 * p.pad - p.filters->height) / p.stride + 1;
	auto filter_group_size = p.filters->num / p.groups;

	for (size_t g = 0; g < p.groups; ++g) {
		for (size_t fg = 0; fg < filter_group_size; ++fg) {
			size_t co = g * filter_group_size + fg;
			sink->set_flt_idx(co);
			for (size_t yo = 0; yo < out_height; ++yo) {
				for (size_t xo = 0; xo < out_width; ++xo) {
					for (size_t cf = 0; cf < p.filters->channels; ++cf) {
						for (size_t yf = 0; yf < p.filters->height; ++yf) {
							for (size_t xf = 0; xf < p.filters->width; ++xf) {
								auto xi = xo * p.stride + xf - p.pad;
								auto yi = yo * p.stride + yf - p.pad;
								auto ci = g * p.filters->channels + cf;
								sink->write_value(get_input_value(input, xi, yi, ci));
							}
						}
					}
					sink->end_dot_prod();
				}
			}
			sink->end_filter();
		}
	}
	sink->end_convolution();
	return sink->make_result_blob(out_width, out_height, p.filters->num);
}

static void read_buffer(void *ptr, size_t size, const string &path) {
	ifstream ifs(path.c_str(), ifstream::in | ifstream::binary);
	if (!ifs || !ifs.read(reinterpret_cast<char *>(ptr), size)) {
		throw Read_buffer_failed { };
	}
}

static auto read_filters(unique_ptr<Blob> filters_mem, const string &path) {
	read_buffer(filters_mem->ptr(), filters_mem->size() * sizeof(float), path);
	return filters_mem;
}

static auto read_bias_vec(vector<float> bias_vec_mem, const string &path) {
	read_buffer(&bias_vec_mem[0], bias_vec_mem.size() * sizeof(float), path);
	return bias_vec_mem;
}

static auto ensure_valid_filters(const Blob &filters) {
	if (filters.width != filters.height || filters.width % 2 == 0) {
		throw Invalid_filters { };
	}
}

static void ensure_bias_vec_matches_filters(const vector<float> &bias_vec, const Blob &filters) {
	if (bias_vec.size() != filters.num) {
		throw Bias_missmatch { };
	}
}

Convolution::Parameters::Parameters(unique_ptr<Blob> filters_mem, const string &filters_path,
		vector<float> bias_vec_mem, const string &bias_vec_path,
		size_t stride, size_t pad, size_t groups) :
		filters { read_filters(move(filters_mem), filters_path) },
				bias_vec { read_bias_vec(move(bias_vec_mem), bias_vec_path) },
				stride { stride }, pad { pad }, groups { groups } {
	ensure_valid_filters(*this->filters);
	ensure_bias_vec_matches_filters(this->bias_vec, *this->filters);
}

const char *Convolution_exception::what() const noexcept {
	return "socs::opencl::Convolution_exception";
}

const char *Read_buffer_failed::what() const noexcept {
	return "socs::opencl::Read_buffer_failed";
}

const char *Bias_missmatch::what() const noexcept {
	return "socs::opencl::Bias_missmatch";
}

const char *Invalid_filters::what() const noexcept {
	return "socs::opencl::Invalid_filters";
}

const char *Invalid_param_index::what() const noexcept {
	return "socs::opencl::Invalid_param_index";
}

const char *Invalid_input::what() const noexcept {
	return "socs::opencl::Invalid_input";
}

}
// namespace opencl
}// namespace socs
