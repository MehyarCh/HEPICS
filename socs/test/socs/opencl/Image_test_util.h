#pragma once

#include "socs/opencl/Blob.h"
#include "socs/Exception.h"
#include <memory>

namespace socs {

using std::unique_ptr;
using std::string;
using opencl::Blob;

struct Image_test_util {
	static unique_ptr<Blob> load_dump(const string &path);
	static bool near_equals(const Blob &a, const Blob &b, float max_error);
	static bool min_max_intersect(const Blob &a, const Blob &b, size_t radius, float max_error);
};

class Load_dump_failed: public Exception {
public:
	const char *what() const noexcept override;
};

} // namespace socs

