#include "Image_test_util.h"

#include <fstream>
#include <algorithm>

namespace socs {

using namespace std;
using namespace opencl;

unique_ptr<Blob> Image_test_util::load_dump(const string &path) {
	ifstream ifs(path.c_str(), ifstream::in | ifstream::binary);
	auto num = 0;
	auto channels = 0;
	auto height = 0;
	auto width = 0;
	if (!ifs ||
			!ifs.read(reinterpret_cast<char *>(&num), sizeof(num)) ||
			!ifs.read(reinterpret_cast<char *>(&channels), sizeof(channels)) ||
			!ifs.read(reinterpret_cast<char *>(&height), sizeof(height)) ||
			!ifs.read(reinterpret_cast<char *>(&width), sizeof(width))) {
		throw Load_dump_failed { };
	}
	auto dump = make_unique<Blob>(width, height, channels, num);
	if (!ifs.read(reinterpret_cast<char *>(dump->ptr()), dump->size() * sizeof(*dump->ptr()))) {
		throw Load_dump_failed { };
	}
	return dump;
}

bool Image_test_util::near_equals(const Blob &a, const Blob &b, float max_error) {
	if (a.num != b.num || a.channels != b.channels ||
			a.height != b.height || a.width != b.width ||
			!(max_error >= 0.0f)) {
		return false;
	}
	for (size_t n = 0; n < a.num; ++n) {
		for (size_t c = 0; c < a.channels; ++c) {
			for (size_t y = 0; y < a.height; ++y) {
				for (size_t x = 0; x < a.width; ++x) {
					auto va = a.at(x, y, c, n);
					auto vb = b.at(x, y, c, n);
					auto error = abs(va - vb);
					if (!(error <= max_error)) {
						return false;
					}
				}
			}
		}
	}
	return true;
}

bool Image_test_util::min_max_intersect(const Blob &a, const Blob &b, size_t radius, float max_error) {
	if (a.num != b.num || a.channels != b.channels ||
			a.height != b.height || a.width != b.width ||
			!(radius >= 0) || !(max_error >= 0.0f)) {
		return false;
	}
	auto size = radius + 1 + radius;
	for (size_t n = 0; n < a.num; ++n) {
		for (size_t c = 0; c < a.channels; ++c) {
			for (size_t y = 0; y < a.height; ++y) {
				for (size_t x = 0; x < a.width; ++x) {
					auto min_a = a.at(x, y, c, n);
					auto max_a = a.at(x, y, c, n);
					auto min_b = b.at(x, y, c, n);
					auto max_b = b.at(x, y, c, n);
					for (size_t j = 0; j < size; ++j) {
						for (size_t i = 0; i < size; ++i) {
							auto pos_x = x - radius + i;
							auto pos_y = y - radius + j;
							if (pos_x < a.width && pos_y < a.height && c < a.channels && n < a.num) {
								auto val_a = a.at(pos_x, pos_y, c, 0);
								min_a = min(min_a, val_a);
								max_a = max(max_a, val_a);
							}
							if (pos_x < b.width && pos_y < b.height && c < b.channels && n < b.num) {
								auto val_b = b.at(pos_x, pos_y, c, 0);
								min_b = min(min_b, val_b);
								max_b = max(max_b, val_b);
							}
						}
					}
					if (min_a > max_b + max_error || min_b > max_a + max_error) {
						return false;
					}
				}
			}
		}
	}
	return true;
}

const char *Load_dump_failed::what() const noexcept {
	return "socs::Load_dump_failed";
}

} // namespace socs
