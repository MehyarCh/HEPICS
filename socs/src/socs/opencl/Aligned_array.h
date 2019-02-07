#pragma once

#include <cstddef>
#include <cstdlib>
#include "../Exception.h"

namespace socs {
namespace opencl {

class Posix_memalign_failed: public Exception {
public:
	const char *what() const noexcept override {
		return "socs::opencl::PosixMemalignFailed";
	}
};

template<class T>
class Aligned_array {
public:
	static constexpr size_t alignment = 64;

	T * const array;
	const size_t length;

private:
	static auto makeArray(size_t length) {
		auto out = static_cast<void *>(nullptr);
		if (posix_memalign(&out, alignment, length * sizeof(T)) != 0) {
			throw Posix_memalign_failed { };
		}
		return static_cast<T *>(out);
	}

public:
	Aligned_array(size_t lenght) :
			array { makeArray(lenght) }, length { lenght } {
	}

	~Aligned_array() {
		free((void *) array);
	}

	Aligned_array(const Aligned_array &a) = delete;
	Aligned_array(const Aligned_array &&a) = delete;
	Aligned_array &operator=(const Aligned_array &a) = delete;
	Aligned_array &operator=(const Aligned_array &&a) = delete;

};

} // namespace opencl
} // namespace socs
