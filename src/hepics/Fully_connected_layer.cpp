#include "Fully_connected_layer.h"

namespace hepics {

using namespace std;

Fully_connected_layer::Fully_connected_layer(const Image &weights, vector<float> bias) :
		weights { weights }, bias { move(bias) } {
}

static void ensure_valid_input_size(const Image &input, const Image &weights) {
	if (input.size() != weights.width) {
		throw Invalid_fully_connected_param { };
	}
}

unique_ptr<Image> Fully_connected_layer::forward_layer(const Image &input) {
	ensure_valid_input_size(input, weights);
	auto output_width = 1;
	auto output_height = 1;
	auto output_channels = weights.height;
	auto output_num = 1;
	auto output = make_unique<Image>(output_width, output_height, output_channels, output_num);

	auto a = input.ptr();
	for (size_t y = 0; y < weights.height; y++) {
		auto sum = 0.0;
		for (size_t x = 0; x < weights.width; x++) {
			sum += weights.at(x, y, 0, 0) * a[x];
		}
		output->at(0, 0, y, 0) = sum + bias[y];
	}
	return output;
}

Layer::Type Fully_connected_layer::get_type() {
	return Type::fullyconnected;
}

const char *Invalid_fully_connected_param::what() const noexcept {
	return "hepics::Invalid_fully_connected_param";
}

} // namespace hepics
