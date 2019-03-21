#pragma once

#include <memory>
#include <vector>
#include <cassert>

namespace socs {
namespace opencl {

using std::vector;

class Blob {
public:
	Blob(size_t width, size_t height, size_t channels, size_t num) :
			width { width }, height { height }, channels { channels },
					num { num }, data(width * height * channels * num) {
	}

	Blob(const Blob &image) = default;
	Blob(const Blob &&image) = delete;
	const Blob &operator=(const Blob &image) = delete;
	const Blob &operator=(const Blob &&image) = delete;

	~Blob() = default;

	size_t size() const {
		return data.size();
	}

	float *ptr() {
		return &data[0];
	}

	const float *ptr() const {
		return &data[0];
	}

	const float &at(size_t x, size_t y, size_t c, size_t n) const {
		assert(x < width && y < height && c < channels && n < num);
		return data[(((n * channels) + c) * height + y) * width + x];
	}

	float &at(size_t x, size_t y, size_t c, size_t n) {
		assert(x < width && y < height && c < channels && n < num);
		return data[(((n * channels) + c) * height + y) * width + x];
	}

	const size_t width;
	const size_t height;
	const size_t channels;
	const size_t num;

private:
	vector<float> data;

};

} // namespace opencl
} // namespace socs
