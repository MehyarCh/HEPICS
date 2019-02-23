#include "Fully_connected_layer.h"

namespace hepics {

using namespace std;

Fully_connected_layer::Fully_connected_layer(const vector<float> &weights) :
		weights { weights } {
}

unique_ptr<Image> Fully_connected_layer::forward_layer(const Image &input) {
	auto output_width = size_t { 0 }; // TODO calculate width
	auto output_height = size_t { 0 }; // TODO calculate height
	auto output_channels = input.channels;
	auto output = make_unique<Image>(output_width, output_height,
			output_channels);
	// TODO fill output
	// TODO the alexnet fully connected layer has 4096 neurons... find out how an image is mapped to that (check caffe code)
	return output;
}

} // namespace hepics
