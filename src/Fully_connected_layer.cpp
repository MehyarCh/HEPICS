#include "Fully_connected_layer.h"

namespace hepics {

using namespace std;

Fully_connected_layer::Fully_connected_layer(const Image &weights) :
		weights { weights } {
}

unique_ptr<Image> Fully_connected_layer::forward_layer(const Image &input) {
	auto output_width = 1; // TODO calculate width
	auto output_height = weights.width; // TODO calculate height
	auto output_channels = 1;
	auto output = make_unique<Image>(output_width, output_height,
			output_channels);

	int counter = 0;
	int s = input.height * input.width * input.channels; // s = size of the image data

	auto inputAs1 = make_unique<Image>(1, s, 1); // input image as a matrix with width 1

	// we are working with the weights as a transformed matrix then we can change it in the constructor after understanding what is the 4d

	for (int c = 0; c < input.channels; c++) {
		for (int y = 0; y < input.height; y++) {
			for (int x = 0; x < input.width; x++) {
				inputAs1->at(0, counter, 0) = input.at(x, y, c);
				counter++;
			}
		}
	}

	for (int x = 0; x < weights.width; x++) { //y
		int counter2 = 0;
		int sum = 0;
		for (int y = 0; y < weights.height; y++) { //s

			sum += weights.at(y, x, 0) * inputAs1->at(0, counter2, 0);
			counter2++;
		}
		output->at(0, x, 0) = sum;
	}

	// TODO fill output
	// TODO the alexnet fully connected layer has 4096 neurons... find out how an image is mapped to that (check caffe code)
	return output;
}

Layer::Type Fully_connected_layer::get_type(){
	return Type::fullyconnected;
}
} // namespace hepics
