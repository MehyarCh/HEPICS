#include "Convolution.h"

namespace socs {
namespace opencl {

using namespace std;

constexpr auto altera_platform_name = "Altera SDK for OpenCL";
constexpr auto de1soc_device_name = "de1soc_sharedonlyCyclone V SoC Development Kit";
constexpr auto cl_path = "kernel/convolution.cl";
constexpr auto aocx_path = "kernel/convolution.aocx";
constexpr auto opencl_kernel_name = "loop_convolution";

Image::Image(uint32_t width, uint32_t height, uint32_t channels, cl_mem_flags flags, const Context &context) :
		width { width }, height { height }, channels { channels },
				data { width * height * channels * sizeof(cl_float), flags, context } {
}

Convolution Convolution::make() {
	auto is_altera = [](const string &name) {return name == altera_platform_name;};
	auto is_de1soc = [](const string &name) {return name == de1soc_device_name;};

	auto platform = Platform { is_altera };
	auto device = Device { is_de1soc, platform };
	auto context = make_shared<Context>(platform, device);
	auto program = is_altera(platform.get_name()) ? make_shared<Program>(aocx_path, *context, device) :
													make_shared<Program>(cl_path, *context);
	program->build(device);
	auto opencl_kernel = make_shared<Kernel>(*program, opencl_kernel_name);
	auto queue = make_shared<Command_queue>(*context, device, false);
	auto dim = make_shared<Buffer>(7 * sizeof(cl_uint), CL_MEM_READ_ONLY, *context);

	return Convolution { platform, device, context, shared_ptr<Program>(program), opencl_kernel, queue };
}

static auto ensure_valid_kernel(const Image &kernel) {
	if (kernel.width != kernel.height || kernel.width % 2 == 0) {
		throw Invalid_kernel_image { };
	}
}

static auto ensure_kernel_fits(const Image &data, const Image &kernel) {
	if (kernel.width > data.width || kernel.height > data.height) {
		throw Kernel_too_big { };
	}
}

unique_ptr<Image> Convolution::run(const Image &data, const Image &kernel, uint32_t stride) const {
	ensure_valid_kernel(kernel);
	ensure_kernel_fits(data, kernel);

	auto dims = make_unique<Buffer>(5 * sizeof(cl_uint), CL_MEM_READ_ONLY, *context);
	auto d = dims->get_array<cl_uint>();
	d[0] = data.width;
	d[1] = data.height;
	d[2] = data.channels;
	d[3] = kernel.width;
	d[4] = stride;

	auto dme = queue->queue_write(*dims);
	auto kde = queue->queue_write(kernel.data);
	auto dde = queue->queue_write(data.data);

	auto x_size = (data.width - kernel.width) / stride + 1;
	auto y_size = (data.height - kernel.height) / stride + 1;
	auto z_size = data.channels;
	auto res = make_unique<Image>(x_size, y_size, z_size, CL_MEM_WRITE_ONLY, *context);

	auto &k = *opencl_kernel;

	k.set_arg(0, data.data);
	k.set_arg(1, kernel.data);
	k.set_arg(2, *dims);
	k.set_arg(3, res->data);

	auto ke = queue->queue_kernel(k, vector<size_t> { x_size, y_size, z_size },
			vector<cl_event> { dme->event, kde->event, dde->event });
	auto re = queue->queue_read(res->data, vector<cl_event> { ke->event });
	Event::wait(vector<cl_event> { re->event });

	return res;
}

const char *Convolution_exception::what() const noexcept {
	return "socs::socket::Convolution_exception";
}

const char *Invalid_kernel_image::what() const noexcept {
	return "socs::socket::Invalid_kernel_image";
}

const char *Kernel_too_big::what() const noexcept {
	return "socs::socket::Kernel_too_big";
}

}
// namespace opencl
}// namespace socs
