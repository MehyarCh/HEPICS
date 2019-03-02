#pragma once

#include <vector>
#include <cstddef>
#include <QImage>
#include <QString>

#include "Exception.h"

namespace hepics {

using std::vector;
using std::string;

class Image {
public:

	Image(size_t width, size_t height, size_t channels, size_t num);

	Image(const Image &image)=default;
	Image(const Image &&image) = delete;
	const Image &operator=(const Image &image) = delete;
	const Image &operator=(const Image &&image) = delete;

	virtual ~Image() = default;

	size_t size() const {
		return data.size();
	}

	float *ptr() {
		return &data[0];
	}

	const float *ptr() const {
		return &data[0];
	}

	const float &at(size_t x, size_t y, size_t c, size_t n) const;
	float &at(size_t x, size_t y, size_t c, size_t n);

	const size_t width;
	const size_t height;
	const size_t channels;
	const size_t num;
	const int id;

	void load_image(string path);
	//Image load_image(char* path, int height ,int length ,int channels);



private:
	vector<float> data;
	static int IDcounter;
};

class No_image_loaded: public Exception {
public:
	const char *what() const noexcept override;
};

} // namespace hepics

