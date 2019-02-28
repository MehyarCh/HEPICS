#include <gtest/gtest.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdint>
#include <memory>
#include <assert.h>
#include <cmath>
#include "Image.h"
#include "Convolutional_layer.h"
using namespace std;
using namespace hepics;
using std::unique_ptr;

namespace Convolutioanl_test {

/**
 * Initialize image data
 */
static auto copy_vector_to_image(Image &image, vector<float> &vec) {
	memcpy(image.ptr(), &vec[0], image.size());
}

static unique_ptr<Image> set_input(vector<float> &data) {
	/* Input */
	auto input = make_unique<Image>(6, 4, 2, 1);

	/* Create Image */
	copy_vector_to_image(*input, data);

	return input;

}

static unique_ptr<Image> set_expected_out(vector<float> &data) {
	/* expected output */
	auto expec_out = make_unique<Image>(4, 2, 2, 1);

	/* Create Image */
	copy_vector_to_image(*expec_out, data);

	return expec_out;

}

static unique_ptr<Image> set_filter(vector<float> &data) {
	/* Filter */
	auto filter = make_unique<Image>(3, 3, 2, 1);

	/* Create filter */
	copy_vector_to_image(*filter, data);

	return filter;

}

static unique_ptr<Convolutional_layer> set_layer(const Image &filter, size_t filter_stride, size_t pad) {
	auto conv_layer = make_unique<Convolutional_layer>(filter, filter_stride, pad);

	return conv_layer;
}

/**
 * filter: 3x3
 * stride: 1
 * pad: 1
 */
TEST(convolution_test, conv_1) {
	vector<float> filter_data = vector<float> {
		0.1, 0.2, 0.3,
		0.4, 0.5, 0.6,
		0.7, 0.8, 0.9,

		0.9, 0.8, 0.7,
		0.6, 0.5, 0.4,
		0.3, 0.2, 0.1,
	};

	vector<float> expec_data = vector<float> {
		11.1, 17.8, 21.7, 14.5,
		6.9, 10.6, 12.7, 7.9,

		7.9, 12.7, 10.6, 6.9,
		14.5, 21.7, 17.8, 11.1,
	};

	vector<float> input_data = vector<float> {
		0, 0, 0, 0, 0, 0,
		0, 1, 2, 3, 4, 0,
		0, 5, 6, 7, 8, 0,
		0, 0, 0, 0, 0, 0,

		0, 0, 0, 0, 0, 0,
		0, 8, 7, 6, 5, 0,
		0, 4, 3, 2, 1, 0,
		0, 0, 0, 0, 0, 0,
	};

	/* Initialize parameters */
	unique_ptr<Image> filter = set_filter(filter_data);
	size_t stride = 1;
	size_t pad = 1;
	auto input = set_input(input_data);
	auto expec_out = set_expected_out(expec_data);

	/* Create a layer*/
	unique_ptr<Convolutional_layer> conv_layer = set_layer(*filter, stride, pad);

	auto out = conv_layer->forward_layer(*input); // run convolutional layer

	ASSERT_EQ(expec_out->width, out->width);
}

/**
 * filter: 1x1
 * stride: 1
 * pad: 1
 */
TEST(convolution_test, conv_2) {
	vector<float> filter_data = vector<float> { 1, 1 };

	vector<float> input_data = vector<float> {
		0, 0, 0, 0, 0, 0,
		0, 1, 2, 3, 4, 0,
		0, 5, 6, 7, 8, 0,
		0, 0, 0, 0, 0, 0,

		0, 0, 0, 0, 0, 0,
		0, 8, 7, 6, 5, 0,
		0, 4, 3, 2, 1, 0,
		0, 0, 0, 0, 0, 0,
	};

	vector<float> expec_data = input_data;

	/* Initialize parameters */
	unique_ptr<Image> filter = set_filter(filter_data);
	size_t stride = 1;
	size_t pad = 1;
	auto input = set_input(input_data);
	auto expec_out = set_expected_out(expec_data);

	/* Create a layer*/
	unique_ptr<Convolutional_layer> conv_layer = set_layer(*filter, stride, pad);

	auto out = conv_layer->forward_layer(*input); // run convolutional layer

	ASSERT_EQ(expec_out->width, out->width);
}

/**
 * filter: 3x3
 * stride: 2
 * pad: 1
 */
TEST(convolution_test, conv_3) {
	vector<float> filter_data = vector<float> {
		0.1, 0.2, 0.3,
		0.4, 0.5, 0.6,
		0.7, 0.8, 0.9,

		0.9, 0.8, 0.7,
		0.6, 0.5, 0.4,
		0.3, 0.2, 0.1,
	};

	vector<float> expec_data = vector<float> {
		11.1, 21.7,

		7.9, 10.6,
};

	vector<float> input_data = vector<float> {
		0, 0, 0, 0, 0, 0,
		0, 1, 2, 3, 4, 0,
		0, 5, 6, 7, 8, 0,
		0, 0, 0, 0, 0, 0,

		0, 0, 0, 0, 0, 0,
		0, 8, 7, 6, 5, 0,
		0, 4, 3, 2, 1, 0,
		0, 0, 0, 0, 0, 0,
	};

	/* Initialize parameters */
	unique_ptr<Image> filter = set_filter(filter_data);
	size_t stride = 1;
	size_t pad = 1;
	auto input = set_input(input_data);
	auto expec_out = set_expected_out(expec_data);

	/* Create a layer*/
	unique_ptr<Convolutional_layer> conv_layer = set_layer(*filter, stride, pad);

	auto out = conv_layer->forward_layer(*input); // run convolutional layer

	ASSERT_EQ(expec_out->width, out->width);
}

/**
 * filter: 3x3
 * stride: 2
 * pad: 3
 */
TEST(convolution_test, conv_4) {
	vector<float> filter_data = vector<float> {
		0.1, 0.2, 0.3,
		0.4, 0.5, 0.6,
		0.7, 0.8, 0.9,

		0.9, 0.8, 0.7,
		0.6, 0.5, 0.4,
		0.3, 0.2, 0.1,
	};

	vector<float> expec_data = vector<float> {
		11.1, 14.5,

		7.9, 6.9,
	};

	vector<float> input_data = vector<float> {
		0, 0, 0, 0, 0, 0,
		0, 1, 2, 3, 4, 0,
		0, 5, 6, 7, 8, 0,
		0, 0, 0, 0, 0, 0,

		0, 0, 0, 0, 0, 0,
		0, 8, 7, 6, 5, 0,
		0, 4, 3, 2, 1, 0,
		0, 0, 0, 0, 0, 0,
	};

	/* Initialize parameters */
	unique_ptr<Image> filter = set_filter(filter_data);
	size_t stride = 1;
	size_t pad = 1;
	auto input = set_input(input_data);
	auto expec_out = set_expected_out(expec_data);

	/* Create a layer*/
	unique_ptr<Convolutional_layer> conv_layer = set_layer(*filter, stride, pad);

	auto out = conv_layer->forward_layer(*input); // run convolutional layer

	ASSERT_EQ(expec_out->width, out->width);
}

}
