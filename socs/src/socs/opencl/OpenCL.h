#pragma once

#include <CL/opencl.h>
#include <memory>
#include <vector>
#include <string>
#include <functional>

#include "../Exception.h"
#include "Aligned_array.h"

namespace socs {
namespace opencl {

using std::vector;
using std::string;
using std::function;
using std::unique_ptr;

using NameFilter = function<bool (const string &)>;

struct Platform {
	Platform(const NameFilter &filter);
	string get_name() const;

	const cl_platform_id id;
};

struct Device {
	Device(const NameFilter &filter, const Platform &platform);
	string get_name() const;

	const cl_device_id id;
	const Platform platform;
};

struct Context {
	Context(const Platform &platform, const Device &device);
	Context(const Context &context) = delete;
	Context(const Context &&context) = delete;
	Context &operator=(const Context &context) = delete;
	Context &operator=(const Context &&context) = delete;
	~Context();

	const cl_context context;
};

struct Buffer {
	Buffer(size_t size, cl_mem_flags flags, const Context &context);
	Buffer(const Buffer &buffer) = delete;
	Buffer(const Buffer &&buffer) = delete;
	Buffer &operator=(const Buffer &buffer) = delete;
	Buffer &operator=(const Buffer &&buffer) = delete;
	~Buffer();

	const cl_mem buffer;
	const size_t size;
	const cl_mem_flags flags;

	Aligned_array<uint8_t> mem;
};

struct Program {
	Program(const string &path, const Context &context);
	Program(const string &path, const Context &context, const Device &device);
	Program(const Program &program) = delete;
	Program(const Program &&program) = delete;
	Program &operator=(const Program &program) = delete;
	Program &operator=(const Program &&program) = delete;
	~Program();

	const cl_program program;
};

struct Kernel {
	Kernel(const Program &program, const string &name);
	Kernel(const Kernel &kernel) = delete;
	Kernel(const Kernel &&kernel) = delete;
	Kernel &operator=(const Kernel &kernel) = delete;
	Kernel &operator=(const Kernel &&kernel) = delete;
	~Kernel();
	void set_arg(cl_uint index, const Buffer &buffer) const;

	const cl_kernel kernel;
};

struct Event {
	Event(cl_event event);
	Event(const Event &event) = delete;
	Event(const Event &&event) = delete;
	Event &operator=(const Event &event) = delete;
	Event &operator=(const Event &&event) = delete;
	~Event();

	const cl_event event;
};

struct Command_queue {
	Command_queue(const Context &context, const Device &device, bool out_of_order_exec = false);
	Command_queue(const Command_queue &queue) = delete;
	Command_queue(const Command_queue &&queue) = delete;
	Command_queue &operator=(const Command_queue &queue) = delete;
	Command_queue &operator=(const Command_queue &&queue) = delete;
	~Command_queue();
	unique_ptr<Event> queue_write(const Buffer &buffer, const vector<cl_event> &wait_list = vector<cl_event> { }) const;
	unique_ptr<Event> queue_read(const Buffer &buffer, const vector<cl_event> &wait_list = vector<cl_event> { }) const;
	unique_ptr<Event> queue_kernel(const Kernel &kernel, const vector<size_t> &work_size,
			const vector<cl_event> &wait_list = vector<cl_event> { }) const;

	const cl_command_queue queue;
};

class OpenCL_exception: public Exception {
public:
	const char *what() const noexcept override;
};

class No_platform: public OpenCL_exception {
public:
	const char *what() const noexcept override;
};

class No_device: public OpenCL_exception {
public:
	const char *what() const noexcept override;
};

class Create_context_failed: public OpenCL_exception {
public:
	const char *what() const noexcept override;
};

class Create_buffer_failed: public OpenCL_exception {
public:
	const char *what() const noexcept override;
};

class Create_program_with_source_failed: public OpenCL_exception {
public:
	const char *what() const noexcept override;
};

class Create_program_with_binary_failed: public OpenCL_exception {
public:
	const char *what() const noexcept override;
};

class Build_program_failed: public OpenCL_exception {
public:
	const char *what() const noexcept override;
};

class Create_kernel_failed: public OpenCL_exception {
public:
	const char *what() const noexcept override;
};

class Set_kernel_arg_failed: public OpenCL_exception {
public:
	const char *what() const noexcept override;
};

class Create_queue_failed: public OpenCL_exception {
public:
	const char *what() const noexcept override;
};

class Equeue_write_failed: public OpenCL_exception {
public:
	const char *what() const noexcept override;
};

class Equeue_read_failed: public OpenCL_exception {
public:
	const char *what() const noexcept override;
};

class Enqueue_kernel_failed: public OpenCL_exception {
public:
	const char *what() const noexcept override;
};

} // namespace opencl
} // namespace socs
