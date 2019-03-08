#pragma once

#include "hepics/Image.h"
#include <memory>

namespace hepics {

using std::unique_ptr;

struct Image_test_util {
	static unique_ptr<Image> load_dump(const string &path);
	static bool near_equals(const Image &a, const Image &b, float max_error);
	static bool min_max_intersect(const Image &a, const Image &b, size_t radius, float max_error);
};

class Load_dump_failed: public Exception {
public:
	const char *what() const noexcept override;
};

} // namespace hepics

