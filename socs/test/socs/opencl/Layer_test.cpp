#include <gtest/gtest.h>
#include "Test_paths.h"
#include "Image_test_util.h"
#include "socs/opencl/Convolution.h"

using namespace std;
using namespace socs;
using namespace socs::opencl;

struct Layer_test {
	string input_path;
	string expected_output_path;
	float max_error;
};

static auto add_layer_dump_path_prefix(vector<Layer_test> layer_tests) {
	for (auto &t : layer_tests) {
		t.input_path = Test_paths::layer_dumps + t.input_path;
		t.expected_output_path = Test_paths::layer_dumps + t.expected_output_path;
	}
	return layer_tests;
}

static auto make_layer_tests() {
	return add_layer_dump_path_prefix(vector<Layer_test> {
		Layer_test{"preprocessed-blob-0", "conv_layer-top-2", 0.001f},
		Layer_test{"pooling_layer-top-8", "conv_layer-top-10", 0.001f},
		Layer_test{"pooling_layer-top-16", "conv_layer-top-18", 0.001f},
		Layer_test{"relu_layer-top-20", "conv_layer-top-22", 0.001f},
		Layer_test{"relu_layer-top-24", "conv_layer-top-26", 0.001f},
	});
}

TEST(layer_test, run_layers) {
#ifndef INCLUDE_SLOW_TESTS
	FAIL();
#endif
	if (Test_paths::layer_dumps == ""s) {
		FAIL();
	}
	auto c = Convolution::make();
	auto layer_tests = make_layer_tests();

	for (size_t i = 0, n = layer_tests.size(); i < n; ++i) {
		auto input = Image_test_util::load_dump(layer_tests[i].input_path);
		auto expected_output = Image_test_util::load_dump(layer_tests[i].expected_output_path);
		auto output = c.run(i, *input);
		ASSERT_TRUE(Image_test_util::near_equals(*output, *expected_output, layer_tests[i].max_error));
	}
}
