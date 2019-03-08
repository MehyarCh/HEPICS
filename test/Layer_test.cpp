#include <gtest/gtest.h>
#include "hepics/Caffemodel.h"
#include "Test_paths.h"
#include "Image_test_util.h"

using namespace std;
using namespace hepics;
using namespace hepics::caffemodel;

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
		Layer_test{"conv_layer-top-2", "relu_layer-top-4", 0.0f},
		Layer_test{"relu_layer-top-4", "lrn_layer-top-6", 0.001f},
		Layer_test{"lrn_layer-top-6", "pooling_layer-top-8", 0.0f},
		Layer_test{"pooling_layer-top-8", "conv_layer-top-10", 0.001f},
		Layer_test{"conv_layer-top-10", "relu_layer-top-12", 0.0f},
		Layer_test{"relu_layer-top-12", "lrn_layer-top-14", 0.001f},
		Layer_test{"lrn_layer-top-14", "pooling_layer-top-16", 0.0f},
		Layer_test{"pooling_layer-top-16", "conv_layer-top-18", 0.001f},
		Layer_test{"conv_layer-top-18", "relu_layer-top-20", 0.0f},
		Layer_test{"relu_layer-top-20", "conv_layer-top-22", 0.001f},
		Layer_test{"conv_layer-top-22", "relu_layer-top-24", 0.0f},
		Layer_test{"relu_layer-top-24", "conv_layer-top-26", 0.001f},
		Layer_test{"conv_layer-top-26", "relu_layer-top-28", 0.0f},
		Layer_test{"relu_layer-top-28", "pooling_layer-top-30", 0.0f},
		Layer_test{"pooling_layer-top-30", "inner_product_layer-top-32", 0.0001f},
		Layer_test{"inner_product_layer-top-32", "relu_layer-top-34", 0.0f},
		Layer_test{"relu_layer-top-34", "inner_product_layer-top-36", 0.0001f},
		Layer_test{"inner_product_layer-top-36", "relu_layer-top-38", 0.0f},
		Layer_test{"relu_layer-top-38", "inner_product_layer-top-40", 0.0001f},
		Layer_test{"inner_product_layer-top-40", "softmax_layer-top-42", 0.000001f},
	});
}

TEST(layer_test, run_layers) {
#ifndef INCLUDE_SLOW_TESTS
	FAIL();
#endif
	if (Test_paths::alexnet_caffemodel == ""s || Test_paths::layer_dumps == ""s) {
		FAIL();
	}
	auto layer_tests = make_layer_tests();
	auto model = Model::parse_layers(Test_paths::alexnet_caffemodel);
	ASSERT_EQ(model.size(), layer_tests.size());

	for (size_t i = 0, n = model.size(); i < n; ++i) {
		auto input = Image_test_util::load_dump(layer_tests[i].input_path);
		auto expected_output = Image_test_util::load_dump(layer_tests[i].expected_output_path);
		auto output = model[i]->forward_layer(*input);
		ASSERT_TRUE(Image_test_util::near_equals(*output, *expected_output, layer_tests[i].max_error));
	}
}
