#include <cassert>
#include "Image.h"
#include <iostream>

namespace hepics {

int Image::IDcounter = 0;

Image::Image(size_t width, size_t height, size_t channels, size_t num) :
		width { width }, height { height }, channels { channels }, num { num }, id {
				++IDcounter }, data(width * height * channels * num) {
}

const float &Image::at(size_t x, size_t y, size_t c, size_t n) const {
	assert(x < width && y < height && c < channels && n < num);
	return data[(((n * channels) + c) * height + y) * width + x];
}

float &Image::at(size_t x, size_t y, size_t c, size_t n) {
	assert(x < width && y < height && c < channels && n < num);
	return data[(((n * channels) + c) * height + y) * width + x];
}

void Image::load_image(string path) {
	const char *conversion = path.c_str();
	QString convert = conversion;

	QImage raw = QImage(convert);
	if (raw.height() == 0 || raw.width() == 0) {
		throw No_image_loaded { };
	}

	QImage resized = raw.scaled(width, height, Qt::IgnoreAspectRatio,
			Qt::SmoothTransformation);
	for (size_t y = 0; y < width; ++y) {
		for (size_t x = 0; x < height; ++x) {
			at(x, y, 0, 0) = resized.pixelColor(x, y).redF();
			at(x, y, 1, 0) = resized.pixelColor(x, y).greenF();
			at(x, y, 2, 0) = resized.pixelColor(x, y).blueF();
		}
	}
}

const char *No_image_loaded::what() const noexcept {
	return "hepics::No_image_loaded";
}

} // namespace hepics
