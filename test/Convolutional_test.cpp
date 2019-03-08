#include <gtest/gtest.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdint>
#include <memory>
#include <assert.h>
#include <cmath>
#include "hepics/Image.h"
#include "hepics/Convolutional_layer.h"
using namespace std;
using namespace hepics;
using std::unique_ptr;

namespace Convolutioanl_test {

/**
 * Initialize image data
 */
static auto copy_vector_to_image(Image &image, vector<float> &vec) {
		memcpy(image.ptr(), &vec[0], image.size() * sizeof(float));

}

static unique_ptr<Image> set_input(vector<float> &data) {
	/* Input */
	auto input = make_unique<Image>(5, 5, 3, 1);

	/* Create Image */
	copy_vector_to_image(*input, data);

	return input;

}

static unique_ptr<Image> set_expected_out(vector<float> &data) {
	/* expected output */
	auto expec_out = make_unique<Image>(3, 3, 2, 1);

	/* Create Image */
	copy_vector_to_image(*expec_out, data);

	return expec_out;

}

static unique_ptr<Image> set_filters(vector<float> &data) {
	/* Filter */
	auto filter = make_unique<Image>(3, 3, 3, 2);

	/* Create filter */
	copy_vector_to_image(*filter, data);

	return filter;

}

static unique_ptr<Convolutional_layer> set_layer(unique_ptr<Image> filters, vector<float> bias, size_t filter_stride, size_t pad) {
	unique_ptr<Convolutional_layer> conv_layer = make_unique<Convolutional_layer>(move (filters), bias, filter_stride, pad, 1);

	return conv_layer;
}

/**
 * filter: 3x3x3
 * num: 2
 * stride: 2
 * pad: 1
 */
TEST(convolution_test, conv_1) {
	vector<float> input_data = vector<float> {
		0, 0, 0, 2, 1,
		0, 0, 1, 0, 1,
		1, 2, 0, 0, 1,
		2, 2, 1, 1, 2,
		2, 2, 1, 2, 0,

		2, 1, 2, 0, 1,
		1, 2, 0, 0, 1,
		1, 1, 2, 2, 1,
		2, 0, 0, 2, 1,
		2, 1, 1, 1, 0,

		2, 1, 0, 1, 2,
		2, 2, 2, 1, 2,
		0, 1, 1, 1, 0,
		2, 0, 1, 1, 1,
		2, 2, 0, 2, 2,
	};

	vector<float> filters_data = vector<float> {
		// filter W0
		1, 1, 1,
		1, 0, 1,
		0, 1, 0,

		-1, -1, 0,
		0, 1, 0,
		1, -1, 0,

		1, 1, -1,
		1, 1, 1,
		-1, 0, -1,

		// filter W1
		0, -1, -1,
		1, 0, 1,
		-1, -1, 0,

		-1, 1, -1,
		-1, 1, -1,
		1, 1, 0,

		0, 1, 1,
		-1, 0, 0,
		0, 1, 1
	};

	vector<float> expected_data = vector<float> {
		3, 7, 6,
		4, 10, 8,
		13, 14, 9,

		6, 6, 4,
		7, -1, 1,
		3, -1, -3
	};

	vector<float> bias = vector<float> {1, 0};

	/* Initialize parameters */
	auto input = set_input(input_data);
	auto filters = set_filters(filters_data);
	size_t stride = 2;
	size_t pad = 1;
	auto expected_out = set_expected_out(expected_data);

	/* Create a layer*/
	unique_ptr<Convolutional_layer> conv_layer = set_layer(move (filters), bias, stride, pad);

	auto out = conv_layer->forward_layer(*input); // run convolutional layer

	ASSERT_EQ(expected_out->width, out->width);
	ASSERT_EQ(expected_out->height, out->height);
	ASSERT_EQ(expected_out->channels, out->channels);
	for (size_t i = 0; i < out->size(); ++i) {
		ASSERT_EQ(*(expected_out->ptr() + i), *(out->ptr() + i));
	}

}

}
