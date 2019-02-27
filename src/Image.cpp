#include <cassert>
#include "Image.h"
#include <iostream>

namespace hepics {

int Image::IDcounter = 0;

Image::Image(size_t width, size_t height, size_t channels) :
		width { width }, height { height }, channels { channels }, id {
				++IDcounter }, data(width * height * channels) {

}

const float &Image::at(size_t x, size_t y, size_t c) const {
	assert(x < width && y < height && c < channels);
	return data[x + y * width + c * height * width];
}

float &Image::at(size_t x, size_t y, size_t c) {
	assert(x < width && y < height && c < channels);
	return data[x + y * width + c * height * width];
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
			at(x, y, 0) = resized.pixelColor(x, y).redF();
			at(x, y, 1) = resized.pixelColor(x, y).greenF();
			at(x, y, 2) = resized.pixelColor(x, y).blueF();
		}
	}
}

const char *No_image_loaded::what() const noexcept {
	return "hepics::No_image_loaded";
}

} // namespace hepics
