#include <gtest/gtest.h>
#include <cstring>
#include <cmath>

#include "../../../src/socs/opencl/Convolution.h"

using namespace std;
using namespace socs;
using namespace socs::opencl;

#if 0

static auto is_near_equal(float a, float b) {
	constexpr float epsilon = 0.0001f;
	return abs(a - b) < epsilon;
}

static auto image_to_string(const Image &image) {
	auto s = string { };
	for (uint32_t k = 0; k < image.channels; ++k) {
		for (uint32_t j = 0; j < image.height; ++j) {
			for (uint32_t i = 0; i < image.width; ++i) {
				auto a = reinterpret_cast<cl_float*>(image.data.mem.array);
				s += to_string(a[k * image.height * image.width + j * image.width + i]) + ", ";
			}
			s += "\n";
		}
		s += "\n";
	}
	return s;
}

static auto get_image_byte_size(const Image &image) {
	return image.data.mem.length;
}

static auto get_vector_byte_size(const vector<cl_float> &vec) {
	return vec.size() * sizeof(vec[0]);
}

static auto copy_vector_to_image(const vector<cl_float> &vec, Image &image) {
	memcpy(image.data.mem.array, &vec[0], image.data.mem.length);
}

static auto make_test_image() {
	return vector<cl_float> {
			0, 0, 0, 0, 0, 0,
			0, 1, 2, 3, 4, 0,
			0, 5, 6, 7, 8, 0,
			0, 0, 0, 0, 0, 0,

			0, 0, 0, 0, 0, 0,
			0, 8, 7, 6, 5, 0,
			0, 4, 3, 2, 1, 0,
			0, 0, 0, 0, 0, 0,
	};
}

static auto make_test_kernel() {
	return vector<cl_float> {
			0.1, 0.2, 0.3,
			0.4, 0.5, 0.6,
			0.7, 0.8, 0.9,

			0.9, 0.8, 0.7,
			0.6, 0.5, 0.4,
			0.3, 0.2, 0.1,
	};
}

TEST(convolution_test, run_3x3_stride_1) {
	auto in_vec = make_test_image();
	auto kernel_vec = make_test_kernel();
	auto expected_image_vec = vector<cl_float> {
			11.1, 17.8, 21.7, 14.5,
			6.9, 10.6, 12.7, 7.9,

			7.9, 12.7, 10.6, 6.9,
			14.5, 21.7, 17.8, 11.1,
	};

	auto convolution = Convolution::make();

	auto in_image = make_unique<Image>(6, 4, 2, CL_MEM_READ_ONLY, *convolution.context);
	ASSERT_EQ(get_vector_byte_size(in_vec), get_image_byte_size(*in_image));
	copy_vector_to_image(in_vec, *in_image);

	auto kernel_image = make_unique<Image>(3, 3, 2, CL_MEM_READ_ONLY, *convolution.context);
	ASSERT_EQ(get_vector_byte_size(kernel_vec), get_image_byte_size(*kernel_image));
	copy_vector_to_image(kernel_vec, *kernel_image);

	auto stride = uint32_t { 1 };
	auto res_image = convolution.run(*in_image, *kernel_image, stride);
	ASSERT_EQ(get_vector_byte_size(expected_image_vec), get_image_byte_size(*res_image));

	auto res_array = reinterpret_cast<cl_float*>(res_image->data.mem.array);
	for (size_t i = 0; i < expected_image_vec.size(); ++i) {
		if (!is_near_equal(res_array[i], expected_image_vec[i])) {
			FAIL()<< res_array[i] << " is not near " << expected_image_vec[i] << image_to_string(*res_image);
		}
	}
}

TEST(convolution_test, run_1x1_stride_1) {
	auto in_vec = make_test_image();
	auto kernel_vec = vector<cl_float> { 1, 1 };
	auto expected_image_vec = in_vec;

	auto convolution = Convolution::make();

	auto in_image = make_unique<Image>(6, 4, 2, CL_MEM_READ_ONLY, *convolution.context);
	ASSERT_EQ(get_vector_byte_size(in_vec), get_image_byte_size(*in_image));
	copy_vector_to_image(in_vec, *in_image);

	auto kernel_image = make_unique<Image>(1, 1, 2, CL_MEM_READ_ONLY, *convolution.context);
	ASSERT_EQ(get_vector_byte_size(kernel_vec), get_image_byte_size(*kernel_image));
	copy_vector_to_image(kernel_vec, *kernel_image);

	auto stride = uint32_t { 1 };
	auto res_image = convolution.run(*in_image, *kernel_image, stride);
	ASSERT_EQ(get_vector_byte_size(expected_image_vec), get_image_byte_size(*res_image));

	auto res_array = reinterpret_cast<cl_float*>(res_image->data.mem.array);
	for (size_t i = 0; i < expected_image_vec.size(); ++i) {
		if (!is_near_equal(res_array[i], expected_image_vec[i])) {
			FAIL()<< res_array[i] << " is not near " << expected_image_vec[i] << image_to_string(*res_image);
		}
	}
}

TEST(convolution_test, run_3x3_stride_2) {
	auto in_vec = make_test_image();
	auto kernel_vec = make_test_kernel();
	auto expected_image_vec = vector<cl_float> {
			11.1, 21.7,

			7.9, 10.6,
	};

	auto convolution = Convolution::make();

	auto in_image = make_unique<Image>(6, 4, 2, CL_MEM_READ_ONLY, *convolution.context);
	ASSERT_EQ(get_vector_byte_size(in_vec), get_image_byte_size(*in_image));
	copy_vector_to_image(in_vec, *in_image);

	auto kernel_image = make_unique<Image>(3, 3, 2, CL_MEM_READ_ONLY, *convolution.context);
	ASSERT_EQ(get_vector_byte_size(kernel_vec), get_image_byte_size(*kernel_image));
	copy_vector_to_image(kernel_vec, *kernel_image);

	auto stride = uint32_t { 2 };
	auto res_image = convolution.run(*in_image, *kernel_image, stride);
	ASSERT_EQ(get_vector_byte_size(expected_image_vec), get_image_byte_size(*res_image));

	auto res_array = reinterpret_cast<cl_float*>(res_image->data.mem.array);
	for (size_t i = 0; i < expected_image_vec.size(); ++i) {
		if (!is_near_equal(res_array[i], expected_image_vec[i])) {
			FAIL()<< res_array[i] << " is not near " << expected_image_vec[i] << image_to_string(*res_image);
		}
	}
}

TEST(convolution_test, run_3x3_stride_3) {
	auto in_vec = make_test_image();
	auto kernel_vec = make_test_kernel();
	auto expected_image_vec = vector<cl_float> {
			11.1, 14.5,

			7.9, 6.9,
	};

	auto convolution = Convolution::make();

	auto in_image = make_unique<Image>(6, 4, 2, CL_MEM_READ_ONLY, *convolution.context);
	ASSERT_EQ(get_vector_byte_size(in_vec), get_image_byte_size(*in_image));
	copy_vector_to_image(in_vec, *in_image);

	auto kernel_image = make_unique<Image>(3, 3, 2, CL_MEM_READ_ONLY, *convolution.context);
	ASSERT_EQ(get_vector_byte_size(kernel_vec), get_image_byte_size(*kernel_image));
	copy_vector_to_image(kernel_vec, *kernel_image);

	auto stride = uint32_t { 3 };
	auto res_image = convolution.run(*in_image, *kernel_image, stride);
	ASSERT_EQ(get_vector_byte_size(expected_image_vec), get_image_byte_size(*res_image));

	auto res_array = reinterpret_cast<cl_float*>(res_image->data.mem.array);
	for (size_t i = 0; i < expected_image_vec.size(); ++i) {
		if (!is_near_equal(res_array[i], expected_image_vec[i])) {
			FAIL()<< res_array[i] << " is not near " << expected_image_vec[i] << image_to_string(*res_image);
		}
	}
}

#endif
