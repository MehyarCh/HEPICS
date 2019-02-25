#include "Function_layer.h"

namespace hepics {

using namespace std;

unique_ptr<Image> Softmax_layer::forward_layer(const Image &input) {
	auto output_width = size_t { 0 }; // TODO calculate width
	auto output_height = size_t { 0 }; // TODO calculate height
	auto output_channels = input.channels;
	auto output = make_unique<Image>(output_width, output_height, output_channels);
	// TODO fill output
	return output;
}
Layer::Type Softmax_layer::get_type(){
	return Type::softmax;
}

unique_ptr<Image> Relu_layer::forward_layer(const Image &input) {
	auto output_width = size_t { 0 }; // TODO calculate width
	auto output_height = size_t { 0 }; // TODO calculate height
	auto output_channels = input.channels;
	auto output = make_unique<Image>(output_width, output_height, output_channels);
	// TODO fill output
	return output;
}
Layer::Type Relu_layer::get_type(){
	return Type::relu;
}

unique_ptr<Image> Sigmoid_layer::forward_layer(const Image &input) {
	auto output_width = size_t { 0 }; // TODO calculate width
	auto output_height = size_t { 0 }; // TODO calculate height
	auto output_channels = input.channels;
	auto output = make_unique<Image>(output_width, output_height, output_channels);
	// TODO fill output
	return output;
}
Layer::Type Sigmoid_layer::get_type(){
	return Layer::Type::sigmoid;
}

unique_ptr<Image> Tanh_layer::forward_layer(const Image &input) {
	auto output_width = size_t { 0 }; // TODO calculate width
	auto output_height = size_t { 0 }; // TODO calculate height
	auto output_channels = input.channels;
	auto output = make_unique<Image>(output_width, output_height, output_channels);
	// TODO fill output
	return output;
}
Layer::Type Tanh_layer::get_type(){
	return Layer::Type::tanh;
}

} // namespace hepics
