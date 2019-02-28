#include "Fully_connected_layer.h"

namespace hepics {

using namespace std;

Fully_connected_layer::Fully_connected_layer(const Image &weights) :
		weights { weights } {
}

unique_ptr<Image> Fully_connected_layer::forward_layer(const Image &input) {
	auto output_width = 1;
	auto output_height = weights.height;
	auto output_channels = 1;
	auto output_num = 1;
	auto output = make_unique<Image>(output_width, output_height,
			output_channels, output_num);

	int counter = 0;
	int s = input.height * input.width * input.channels * input.num; // s = size of the image data

	auto inputAs1 = make_unique<Image>(1, s, 1, 1); // input image as a matrix with width 1

	for (size_t n = 0; n < input.num; n++) {
			for (size_t c = 0; c < input.channels; c++) {
				for (size_t y = 0; y < input.height; y++) {
					for (size_t x = 0; x < input.width; x++) {
						inputAs1->at(0, counter, 0, 0) = input.at(x, y, c, n);
						counter++;
					}
				}
			}
	}

	for (size_t y = 0; y < weights.height; y++) {
		size_t sum = 0;
		for (size_t x = 0; x < weights.width; x++) {
			sum += weights.at(x, y, 0, 0) * inputAs1->at(0, x, 0, 0);
		}
		output->at(0, y, 0, 0) = sum;
	}
	return output;
}

Layer::Type Fully_connected_layer::get_type() {
	return Type::fullyconnected;
}
} // namespace hepics
