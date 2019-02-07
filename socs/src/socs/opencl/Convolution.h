#pragma once

#include <cstdint>
#include "OpenCL.h"

namespace socs {
namespace opencl {

using std::shared_ptr;

struct Image {
	Image(uint32_t width, uint32_t height, uint32_t channels, cl_mem_flags flags, const Context &context);

	const uint32_t width;
	const uint32_t height;
	const uint32_t channels;
	const Buffer data;
};

struct Convolution {
	static Convolution make();
	unique_ptr<Image> run(const Image &data, const Image &kernel) const;

	const Platform platform;
	const Device device;
	const shared_ptr<Context> context;
	const shared_ptr<Program> program;
	const shared_ptr<Kernel> loop_kernel;
	const shared_ptr<Command_queue> queue;
};

} // namespace opencl
} // namespace socs
