#include "Function_layer.h"
#include <limits>
#include <cmath>

namespace hepics {

using namespace std;

static float relu_activate(float x) {
	return x * (x > 0);
}

static auto get_image_max_value(const Image &image) {
	auto *a = &image.at(0, 0, 0, 0);
	float max_value = numeric_limits<float>().lowest();
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

static void multiply_image_by_value(Image &image, float value) {
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
					output->at(xi, yi, ci, ni) = relu_activate(in_pixel_val);
				}
			}
		}
	}

	return output;
}
Layer::Type Relu_layer::get_type() {
	return Type::relu;
}

} // namespace hepics
