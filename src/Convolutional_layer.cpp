#include "Convolutional_layer.h"

namespace hepics {

using namespace std;

static void ensure_valid_filters(const Image &filters) {
	if (filters.width != filters.height || filters.width % 2 != 1) {
		throw Invalid_convolution_param { };
	}
}

static void ensure_filters_can_be_grouped(const Image &filters, size_t groups) {
	if(filters.num % groups != 0) {
		throw Invalid_convolution_param { };
	}
}

static void ensure_filters_match_bias(const Image &filters, const vector<float> &bias) {
	if (filters.num != bias.size()) {
		throw Invalid_convolution_param { };
	}
}

Convolutional_layer::Convolutional_layer(unique_ptr<Image> filters, vector<float> bias, size_t stride, size_t pad,
		size_t groups) :
		filters { move(filters) }, bias { move(bias) }, stride { stride }, pad { pad }, groups { groups } {
	ensure_valid_filters(*this->filters);
	ensure_filters_can_be_grouped(*this->filters, this->groups);
	ensure_filters_match_bias(*this->filters, this->bias);
}

static void ensure_valid_input(const Image &input, const Image &filters, size_t groups) {
	if (input.channels != groups * filters.channels || input.num != 1) {
		throw Invalid_convolution_param { };
	}
}

static auto get_input_value(const Image &input, size_t x, size_t y, size_t c, size_t n) {
	return x < input.width && y < input.height && c < input.channels && n < input.num ? input.at(x, y, c, n) : 0;
}

unique_ptr<Image> Convolutional_layer::forward_layer(const Image &input) {
	ensure_valid_input(input, *filters, groups);
	auto out_width = (input.width + 2 * pad - filters->width) / stride + 1;
	auto out_height = (input.height + 2 * pad - filters->height) / stride + 1;

	auto filter_group_size = filters->num / groups;

	auto out = make_unique<Image>(out_width, out_height, filters->num, 1);

	for (size_t g = 0; g < groups; ++g) {
		for (size_t fg = 0; fg < filter_group_size; ++fg) {
			size_t co = g * filter_group_size + fg;
			for (size_t yo = 0; yo < out_height; ++yo) {
				for (size_t xo = 0; xo < out_width; ++xo) {
					auto sum = 0.0;
					for (size_t cf = 0; cf < filters->channels; ++cf) {
						for (size_t yf = 0; yf < filters->height; ++yf) {
							for (size_t xf = 0; xf < filters->width; ++xf) {
								auto xi = xo * stride + xf - pad;
								auto yi = yo * stride + yf - pad;
								auto ci = g * filters->channels + cf;
								sum += get_input_value(input, xi, yi, ci, 0) * filters->at(xf, yf, cf, co);
							}
						}
					}
					out->at(xo, yo, co, 0) = float(sum) + bias[co];
				}
			}
		}
	}
	return out;
}

Layer::Type Convolutional_layer::get_type() {
	return Layer::Type::convolutional;
}

const char *Invalid_convolution_param::what() const noexcept {
	return "hepics::Invalid_convolution_param";
}

} // namespace hepics
