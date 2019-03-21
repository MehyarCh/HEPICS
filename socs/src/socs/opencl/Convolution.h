#pragma once

#include <memory>
#include <cstdint>
#include "Blob.h"
#include "OpenCL.h"

namespace socs {
namespace opencl {

using std::unique_ptr;
using std::shared_ptr;

struct Convolution {
	struct Parameters;

	static Convolution make();
	unique_ptr<Blob> run(size_t param_index, const Blob &input) const;


	const Platform platform;
	const Device device;
	const shared_ptr<Context> context;
	const shared_ptr<Program> program;
	const shared_ptr<Kernel> opencl_kernel;
	const shared_ptr<Command_queue> queue;
	const vector<shared_ptr<const Parameters>> params;
};

struct Convolution::Parameters {
	Parameters(unique_ptr<Blob> filters_mem, const string &filters_path,
			vector<float> bias_vec_mem, const string &bias_vec_path,
			size_t stride, size_t pad, size_t groups);

	const shared_ptr<const Blob> filters;
	const vector<float> bias_vec;
	const size_t stride;
	const size_t pad;
	const size_t groups;
};

class Convolution_exception: public Exception {
public:
	const char *what() const noexcept override;
};

class Read_buffer_failed: public Convolution_exception {
public:
	const char *what() const noexcept override;
};

class Bias_missmatch: public Convolution_exception {
public:
	const char *what() const noexcept override;
};

class Invalid_filters: public Convolution_exception {
public:
	const char *what() const noexcept override;
};

class Invalid_param_index: public Convolution_exception {
public:
	const char *what() const noexcept override;
};

class Invalid_input: public Convolution_exception {
public:
	const char *what() const noexcept override;
};

} // namespace opencl
} // namespace socs
