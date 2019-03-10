#include <cassert>
#include "Image.h"
#include <iostream>

namespace hepics {

atomic_int Image::IDcounter(0);

Image::Image(size_t width, size_t height, size_t channels, size_t num) :
		width { width }, height { height }, channels { channels }, num { num }, id {
				IDcounter++ }, data(width * height * channels * num) {
}

const float &Image::at(size_t x, size_t y, size_t c, size_t n) const {
	assert(x < width && y < height && c < channels && n < num);
	return data[(((n * channels) + c) * height + y) * width + x];
}

float &Image::at(size_t x, size_t y, size_t c, size_t n) {
	assert(x < width && y < height && c < channels && n < num);
	return data[(((n * channels) + c) * height + y) * width + x];
}

void Image::load_image(string path, const vector<float> &mean_vector) {
	const char *conversion = path.c_str();
	QString convert = conversion;

	QImage raw = QImage(convert);
	if (raw.height() == 0 || raw.width() == 0) {
		throw No_image_loaded { };
	}

	QImage resized = raw.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	for (size_t y = 0; y < width; ++y) {
		for (size_t x = 0; x < height; ++x) {
			auto rgb = resized.pixel(x, y);
			auto r = float(rgb >> 16 & 0xff);
			auto g = float(rgb >> 8 & 0xff);
			auto b = float(rgb & 0xff);
			at(x, y, 0, 0) = b - mean_vector[0];
			at(x, y, 1, 0) = g - mean_vector[1];
			at(x, y, 2, 0) = r - mean_vector[2];
		}
	}
}

const char *No_image_loaded::what() const noexcept {
	return "hepics::No_image_loaded";
}

} // namespace hepics
