#include <vector>
#include <fstream>

#include "OpenCL.h"
#include "../make_ptr.h"

namespace socs {
namespace opencl {

using namespace std;

static auto get_platform_ids() {
	auto np = cl_uint { 0 };
	if (clGetPlatformIDs(0, nullptr, &np) != CL_SUCCESS) {
		throw OpenCL_exception { };
	}
	if (np == 0) {
		throw No_platform { };
	}
	auto ids = vector<cl_platform_id>(np);
	if (clGetPlatformIDs(ids.size(), &ids[0], nullptr) != CL_SUCCESS) {
		throw OpenCL_exception { };
	}
	return ids;
}

static auto get_platform_name(cl_platform_id platform_id) {
	auto length = size_t { 0 };
	if (clGetPlatformInfo(platform_id, CL_PLATFORM_NAME, 0, nullptr,
			&length) != CL_SUCCESS) {
		throw OpenCL_exception { };
	}
	auto buffer = vector<char>(length);
	if (clGetPlatformInfo(platform_id, CL_PLATFORM_NAME, buffer.size(),
			&buffer[0], nullptr) != CL_SUCCESS) {
		throw OpenCL_exception { };
	}
	return string { &buffer[0] };
}

static auto choose_platform(const vector<cl_platform_id> &ids, const NameFilter &filter) {
	for (auto id : ids) {
		if (filter(get_platform_name(id))) {
			return id;
		}
	}
	return ids[0];
}

static auto get_platform(const NameFilter &filter) {
	auto ids = get_platform_ids();
	return choose_platform(ids, filter);
}

Platform::Platform(const NameFilter &filter) :
		id { get_platform(filter) } {
}

string Platform::get_name() const {
	return get_platform_name(id);
}

static auto get_device_ids(cl_platform_id platform_id) {
	auto nd = cl_uint { 0 };
	if (clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, 0, nullptr,
			&nd) != CL_SUCCESS) {
		throw OpenCL_exception { };
	}
	if (nd == 0) {
		throw No_device { };
	}
	auto ids = vector<cl_device_id>(nd);
	if (clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, ids.size(), &ids[0],
			nullptr) != CL_SUCCESS) {
		throw OpenCL_exception { };
	}
	return ids;
}

static auto get_device_name(cl_device_id device_id) {
	auto length = size_t { 0 };
	if (clGetDeviceInfo(device_id, CL_DEVICE_NAME, 0, nullptr,
			&length) != CL_SUCCESS) {
		throw OpenCL_exception { };
	}
	auto buffer = vector<char>(length);
	if (clGetDeviceInfo(device_id, CL_DEVICE_NAME, buffer.size(), &buffer[0],
			nullptr) != CL_SUCCESS) {
		throw OpenCL_exception { };
	}
	return string { &buffer[0] };
}

static auto choose_device(const vector<cl_device_id> &ids, const NameFilter &filter) {
	for (auto id : ids) {
		if (filter(get_device_name(id))) {
			return id;
		}
	}
	return ids[0];
}

static auto get_device(const NameFilter &filter, const Platform &platform) {
	auto ids = get_device_ids(platform.id);
	return choose_device(ids, filter);
}

Device::Device(const NameFilter &filter, const Platform &platform) :
		id { get_device(filter, platform) }, platform { platform } {
}

string Device::get_name() const {
	return get_device_name(id);
}

static auto make_context(const Platform &platform, const Device &device) {
	auto props = vector<cl_context_properties> {
			static_cast<cl_context_properties>(CL_CONTEXT_PLATFORM),
			reinterpret_cast<cl_context_properties>(platform.id),
			static_cast<cl_context_properties>(0),
	};
	auto context = clCreateContext(&props[0], 1, &device.id, nullptr, nullptr,
			nullptr);
	if (context == nullptr) {
		throw Create_context_failed { };
	}
	return context;
}

Context::Context(const Platform &platform, const Device &device) :
		context { make_context(platform, device) } {
}

Context::~Context() {
	clReleaseContext(context);
}

static auto make_buffer(size_t size, cl_mem_flags flags, const Context &context) {
	auto buffer = clCreateBuffer(context.context, flags, size, nullptr, nullptr);
	if (buffer == nullptr) {
		throw Create_buffer_failed { };
	}
	return buffer;
}

Buffer::Buffer(size_t size, cl_mem_flags flags, const Context &context) :
		buffer { make_buffer(size, flags, context) }, mem { size } {
}

Buffer::~Buffer() {
	clReleaseMemObject(buffer);
}

static auto read_file(const string &path) {
	auto stream = make_unique<ifstream>(path, ios_base::in | ios_base::binary);
	if (!stream->good()) {
		throw Read_file_failed { };
	}
	stream->seekg(0, ifstream::end);
	auto size = stream->tellg();
	if (size == -1) {
		throw Read_file_failed { };
	}
	stream->seekg(0, ifstream::beg);
	auto buffer = vector<uint8_t>(size);
	stream->read(reinterpret_cast<char *>(&buffer[0]), buffer.size());
	return buffer;
}

static auto create_program_with_source(const string &path, const Context &context) {
	auto buffer = read_file(path);
	auto strings = vector<const char *> { reinterpret_cast<const char *>(&buffer[0]) };
	auto lengths = vector<size_t> { buffer.size() };
	auto program = clCreateProgramWithSource(context.context, strings.size(), &strings[0], &lengths[0], nullptr);
	if (program == nullptr) {
		throw Create_program_with_source_failed { };
	}
	return program;
}

Program::Program(const string &path, const Context &context) :
		program { create_program_with_source(path, context) } {
}

static auto create_program_with_binary(const string &path, const Context &context, const Device &device) {
	auto buffer = read_file(path);
	auto lengths = vector<size_t> { buffer.size() };
	auto binaries = vector<const unsigned char *> { reinterpret_cast<const unsigned char *>(&buffer[0]) };
	auto program = clCreateProgramWithBinary(context.context, 1, &device.id, &lengths[0], &binaries[0], nullptr,
			nullptr);
	if (program == nullptr) {
		throw Create_program_with_binary_failed { };
	}
	return program;
}

Program::Program(const string &path, const Context &context, const Device &device) :
		program { create_program_with_binary(path, context, device) } {
}

Program::~Program() {
	clReleaseProgram(program);
}

auto get_build_log(const Program &program, const Device &device) {
	auto size = size_t { 0 };
	if (clGetProgramBuildInfo(program.program, device.id, CL_PROGRAM_BUILD_LOG, 0, nullptr, &size) != CL_SUCCESS) {
		return string { };
	}
	auto log = vector<char>(size);
	if (clGetProgramBuildInfo(program.program, device.id, CL_PROGRAM_BUILD_LOG, log.size(), &log[0],
			nullptr) != CL_SUCCESS) {
		return string { };
	}
	return string { log.begin(), log.end() };

}

void Program::build(const Device &device) const {
	auto device_vec = vector<cl_device_id> { device.id };
	if (clBuildProgram(program, device_vec.size(), &device_vec[0], "", nullptr, nullptr) != CL_SUCCESS) {
		throw Build_program_failed { get_build_log(*this, device) };
	}
}

static auto create_kernel(const Program &program, const string &name) {
	auto kernel = clCreateKernel(program.program, name.c_str(), nullptr);
	if (kernel == nullptr) {
		throw Create_kernel_failed { };
	}
	return kernel;
}

Kernel::Kernel(const Program &program, const string &name) :
		kernel { create_kernel(program, name) } {
}

Kernel::~Kernel() {
	clReleaseKernel(kernel);
}

void Kernel::set_arg(cl_uint index, const Buffer &buffer) const {
	if (clSetKernelArg(kernel, index, sizeof(buffer.buffer), &buffer.buffer) != CL_SUCCESS) {
		throw Set_kernel_arg_failed { };
	}
}

void Kernel::set_arg(cl_uint index, int i) const {
	if (clSetKernelArg(kernel, index, sizeof(i), &i) != CL_SUCCESS) {
		throw Set_kernel_arg_failed { };
	}
}

Event::Event(cl_event event) :
		event { event } {
}

Event::~Event() {
	clReleaseEvent(event);
}

void Event::wait(const vector<cl_event> &wait_list) {
	if (wait_list.empty()) {
		return;
	}
	if (clWaitForEvents(wait_list.size(), &wait_list[0]) != CL_SUCCESS) {
		throw Wait_failed { };
	}
}

static auto make_queue(const Context &context, const Device &device, bool out_of_order_exec) {
	auto flags = cl_queue_properties { 0 };
	if (out_of_order_exec) {
		flags |= CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE;
	}
	auto props = vector<cl_queue_properties> { };
	if (flags != 0) {
		props.push_back(CL_QUEUE_PROPERTIES);
		props.push_back(flags);
	}
	props.push_back(0);
	auto queue = clCreateCommandQueueWithProperties(context.context, device.id, &props[0], nullptr);
	if (queue == nullptr) {
		throw Create_queue_failed { };
	}
	return queue;
}

Command_queue::Command_queue(const Context &context, const Device &device, bool out_of_order_exec) :
		queue { make_queue(context, device, out_of_order_exec) } {
}

Command_queue::~Command_queue() {
	clReleaseCommandQueue(queue);
}

unique_ptr<Event> Command_queue::queue_write(const Buffer &buffer, const vector<cl_event> &wait_list,
		size_t limit) const {
	auto ws = wait_list.size();
	auto wl = ws != 0 ? &wait_list[0] : nullptr;
	auto event = cl_event { nullptr };
	if (clEnqueueWriteBuffer(queue, buffer.buffer, CL_FALSE,
			0, min(buffer.mem.length, limit), buffer.mem.array,
			ws, wl, &event) != CL_SUCCESS) {
		throw Equeue_write_failed { };
	}
	return make_unique<Event>(event);
}

unique_ptr<Event> Command_queue::queue_read(const Buffer &buffer, const vector<cl_event> &wait_list) const {
	auto ws = wait_list.size();
	auto wl = ws != 0 ? &wait_list[0] : nullptr;
	auto event = cl_event { nullptr };
	if (clEnqueueReadBuffer(queue, buffer.buffer, CL_FALSE,
			0, buffer.mem.length, buffer.mem.array,
			ws, wl, &event) != CL_SUCCESS) {
		throw Equeue_read_failed { };
	}
	return make_unique<Event>(event);
}

unique_ptr<Event> Command_queue::queue_kernel(const Kernel &kernel, const vector<size_t> &work_size,
		const vector<size_t> &local_size, const vector<cl_event> &wait_list) const {
	if (work_size.size() != local_size.size()) {
		throw Invalid_local_size { };
	}
	auto ws = wait_list.size();
	auto wl = ws != 0 ? &wait_list[0] : nullptr;
	auto event = cl_event { nullptr };
	if (clEnqueueNDRangeKernel(queue, kernel.kernel, work_size.size(), nullptr, &work_size[0], &local_size[0], ws, wl,
			&event) != CL_SUCCESS) {
		throw Enqueue_kernel_failed { };
	}
	return make_unique<Event>(event);
}

const char *OpenCL_exception::what() const noexcept {
	return "socs::socket::Ocl_exception";
}

const char *No_platform::what() const noexcept {
	return "socs::socket::No_platform";
}

const char *No_device::what() const noexcept {
	return "socs::socket::No_device";
}

const char *Create_context_failed::what() const noexcept {
	return "socs::socket::Create_context_failed";
}

const char *Create_buffer_failed::what() const noexcept {
	return "socs::socket::Create_buffer_failed";
}

const char *Create_queue_failed::what() const noexcept {
	return "socs::socket::Create_queue_failed";
}

const char *Equeue_write_failed::what() const noexcept {
	return "socs::socket::Equeue_write_failed";
}

const char *Equeue_read_failed::what() const noexcept {
	return "socs::socket::Equeue_read_failed";
}

const char *Read_file_failed::what() const noexcept {
	return "socs::socket::Read_file_failed";
}

const char *Create_program_with_source_failed::what() const noexcept {
	return "socs::socket::Create_program_with_source_failed";
}

const char *Create_program_with_binary_failed::what() const noexcept {
	return "socs::socket::Create_program_with_binary_failed";
}

Build_program_failed::Build_program_failed(const string &log) :
		log { string("socs::socket::Build_program_failed\n") + log } {
}

const char *Build_program_failed::what() const noexcept {
	return log.c_str();
}

const char *Create_kernel_failed::what() const noexcept {
	return "socs::socket::Create_kernel_failed";
}

const char *Set_kernel_arg_failed::what() const noexcept {
	return "socs::socket::Set_kernel_arg_failed";
}

const char *Enqueue_kernel_failed::what() const noexcept {
	return "socs::socket::Enqueue_kernel_failed";
}

const char *Wait_failed::what() const noexcept {
	return "socs::socket::Wait_failed";
}

const char *Invalid_local_size::what() const noexcept {
	return "socs::socket::Invalid_local_size";
}

} // namespace opencl
} // namespace socs
