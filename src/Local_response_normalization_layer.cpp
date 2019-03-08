#include "Local_response_normalization_layer.h"
#include <cmath>
#include <iostream>

namespace hepics {

using namespace std;

Local_response_normalization_layer::Local_response_normalization_layer() {

}

unique_ptr<Image> Local_response_normalization_layer::forward_layer(const Image &input) {

	auto output_width = input.width;
	auto output_height = input.height;
	auto output_channels = input.channels;
	auto output_num = input.num;

	auto output = make_unique<Image>(output_width, output_height, output_channels, output_num);

	constexpr auto radius = size_t { 2 };
	constexpr auto local_size = size_t { radius + 1 + radius };
	constexpr auto alpha = 0.0001f;
	constexpr auto beta = 0.75f;

	for (size_t n = 0; n < output->num; n++) {
		for (size_t y = 0; y < output->height; y++) {
			for (size_t x = 0; x < output->width; x++) {
				for (size_t c = 0; c < output->channels; c++) {
					auto sum = 0.0;
					for (size_t i = 0; i < local_size; ++i) {
						auto pos = c - radius + i;
						if(pos < output->channels) {
							auto value = input.at(x, y, pos, n);
							sum += value * value;
						}
					}
					output->at(x, y, c, n) = input.at(x, y, c, n) / pow(1.0 + alpha / local_size * sum, beta);
				}
			}
		}
	}
	return output;
}
Layer::Type Local_response_normalization_layer::get_type() {
	return Type::local_response_normalization;
}

} // namespace hepics
