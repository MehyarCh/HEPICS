#include "Function_layer.h"
#include <limits>
#include <cmath>

namespace hepics {

using namespace std;

float Activation::stair_activate(float x) {
	int n = floor(x);
	if (n % 2 == 0)
		return floor(x / 2.);
	else
		return (x - n) + floor(x / 2.);
}
float Activation::hardtan_activate(float x) {
	if (x < -1)
		return -1;
	if (x > 1)
		return 1;
	return x;
}
float Activation::linear_activate(float x) {
	return x;
}
float Activation::logistic_activate(float x) {
	return 1. / (1. + exp(-x));
}
float Activation::loggy_activate(float x) {
	return 2. / (1. + exp(-x)) - 1;
}
float Activation::relu_activate(float x) {
	return x * (x > 0);
}
float Activation::elu_activate(float x) {
	return (x >= 0) * x + (x < 0) * (exp(x) - 1);
}
float Activation::selu_activate(float x) {
	return (x >= 0) * 1.0507 * x + (x < 0) * 1.0507 * 1.6732 * (exp(x) - 1);
}
float Activation::relie_activate(float x) {
	return (x > 0) ? x : .01 * x;
}
float Activation::ramp_activate(float x) {
	return x * (x > 0) + .1 * x;
}
float Activation::leaky_activate(float x) {
	return (x > 0) ? x : .1 * x;
}
float Activation::tanh_activate(float x) {
	return (exp(2 * x) - 1) / (exp(2 * x) + 1);
}
float Activation::plse_activate(float x) {
	if (x < -4)
		return .01 * (x + 4);
	if (x > 4)
		return .01 * (x - 4) + 1;
	return .125 * x + .5;
}

float Activation::lhtan_activate(float x) {
	if (x < 0)
		return .001 * x;
	if (x > 1)
		return .001 * (x - 1) + 1;
	return x;
}

float Activation::activate(float x, ACTIVATION a) {
	switch (a) {
	case LINEAR:
		return linear_activate(x);
	case LOGISTIC:
		return logistic_activate(x);
	case LOGGY:
		return loggy_activate(x);
	case RELU:
		return relu_activate(x);
	case ELU:
		return elu_activate(x);
	case SELU:
		return selu_activate(x);
	case RELIE:
		return relie_activate(x);
	case RAMP:
		return ramp_activate(x);
	case LEAKY:
		return leaky_activate(x);
	case TANH:
		return tanh_activate(x);
	case PLSE:
		return plse_activate(x);
	case STAIR:
		return stair_activate(x);
	case HARDTAN:
		return hardtan_activate(x);
	case LHTAN:
		return lhtan_activate(x);
	}
	return 0;
}

static auto get_image_max_value(const Image &image) {
	auto *a = &image.at(0, 0, 0, 0);
	float max_value = numeric_limits<float>().min();
	for (size_t i = 0, n = image.size(); i < n; ++i) {
		if (a[i] > max_value) {
			max_value = a[i];
		}
	}
	return max_value;
}

static void subtract_value_from_image(const Image &input, float value, Image &output) {
	auto *in = &input.at(0, 0, 0, 0);
	auto *out = &output.at(0, 0, 0, 0);
	for (size_t i = 0, n = input.size(); i < n; ++i) {
		out[i] = in[i] - value;
	}
}

static void exp_image(Image &image) {
	auto *a = &image.at(0, 0, 0, 0);
	for (size_t i = 0, n = image.size(); i < n; ++i) {
		a[i] = exp(a[i]);
	}
}

static auto sum_image(const Image &image) {
	auto sum = 0.0;
	auto *a = &image.at(0, 0, 0, 0);
	for (size_t i = 0, n = image.size(); i < n; ++i) {
		sum += a[i];
	}
	return float(sum);
}

static auto multiply_image_by_value(Image &image, float value) {
	auto *a = &image.at(0, 0, 0, 0);
	for (size_t i = 0, n = image.size(); i < n; ++i) {
		a[i] *= value;
	}
}

unique_ptr<Image> Softmax_layer::forward_layer(const Image &input) {
	auto output_width = input.width;
	auto output_height = input.height;
	auto output_channels = input.channels;
	auto output_num = input.num;
	auto output = make_unique<Image>(output_width, output_height, output_channels, output_num);

	auto max_value = get_image_max_value(input);
	subtract_value_from_image(input, max_value, *output);
	exp_image(*output);
	auto sum = sum_image(*output);
	multiply_image_by_value(*output, 1.0f / sum);

	return output;
}

Layer::Type Softmax_layer::get_type() {
	return Type::softmax;
}

unique_ptr<Image> Relu_layer::forward_layer(const Image &input) {
	auto output_width = input.width;
	auto output_height = input.height;
	auto output_channels = input.channels;
	auto output_num = input.num;
	auto output = make_unique<Image>(output_width, output_height, output_channels, output_num);

	/* Get Input Dimensions */
	size_t in_width = input.width;
	size_t in_height = input.height;
	size_t in_channels = input.channels;
	size_t in_num = input.num;
	float in_pixel_val; /* Input Pixel Value */

	/* Go through input image and activate every pixel */
	for (size_t ni = 0; ni < in_num; ni++) {
		for (size_t ci = 0; ci < in_channels; ci++) {
			for (size_t yi = 0; yi < in_height; yi++) {
				for (size_t xi = 0; xi < in_width; xi++) {
					/* Get next pixel value */
					in_pixel_val = input.at(xi, yi, ci, ni);
					/* activate */
					output->at(xi, yi, ci, ni) = Activation::relu_activate(in_pixel_val);
				}
			}
		}
	}

	return output;
}
Layer::Type Relu_layer::get_type() {
	return Type::relu;
}

unique_ptr<Image> Sigmoid_layer::forward_layer(const Image &input) {
	auto output_width = size_t { 0 }; // TODO calculate width
	auto output_height = size_t { 0 }; // TODO calculate height
	auto output_channels = input.channels;
	auto output_num = input.num;
	auto output = make_unique<Image>(output_width, output_height, output_channels, output_num);
	// TODO fill output
	return output;
}
Layer::Type Sigmoid_layer::get_type() {
	return Layer::Type::sigmoid;
}

unique_ptr<Image> Tanh_layer::forward_layer(const Image &input) {
	auto output_width = size_t { 0 }; // TODO calculate width
	auto output_height = size_t { 0 }; // TODO calculate height
	auto output_channels = input.channels;
	auto output_num = input.num;
	auto output = make_unique<Image>(output_width, output_height, output_channels, output_num);
	// TODO fill output
	return output;
}
Layer::Type Tanh_layer::get_type() {
	return Layer::Type::tanh;
}

} // namespace hepics
