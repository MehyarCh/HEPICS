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
	unique_ptr<Image> run(const Image &data, const Image &kernel, uint32_t stride) const;

	const Platform platform;
	const Device device;
	const shared_ptr<Context> context;
	const shared_ptr<Program> program;
	const shared_ptr<Kernel> opencl_kernel;
	const shared_ptr<Command_queue> queue;
};

class Convolution_exception: public Exception {
public:
	const char *what() const noexcept override;
};

class Invalid_kernel_image: public Convolution_exception {
public:
	const char *what() const noexcept override;
};

class Kernel_too_big: public Convolution_exception {
public:
	const char *what() const noexcept override;
};

} // namespace opencl
} // namespace socs
