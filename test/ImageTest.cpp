#include "Image.h"
#include <gtest/gtest.h>

#include "Test_paths.h"
#include "Image_test_util.h"

using namespace std;
using namespace hepics;

Image *input_image;
Image *second_input;

void test_constructor() {
	second_input = new Image(227, 226, 3, 1);
}

TEST(image_test, test_constructor) {
	test_constructor();
	ASSERT_EQ(second_input->height, 226);
	ASSERT_EQ(second_input->width, 227);
	ASSERT_EQ(second_input->channels, 3);
	ASSERT_EQ(second_input->num, 1);
}

TEST(image_test, test_load_image) {
	if (Test_paths::socker_ball_image == ""s ||
			Test_paths::socker_ball_image_dump == ""s) {
		return;
	}
	auto mean_vector = vector<float> { 104.0f, 116.7f, 122.7f };
	auto input_image = make_unique<Image>(227, 227, 3, 1);
	input_image->load_image(Test_paths::socker_ball_image, mean_vector);
	auto dump = Image_test_util::load_dump(Test_paths::socker_ball_image_dump);
	ASSERT_TRUE(Image_test_util::min_max_intersect(*input_image, *dump, 1, 0.1f));
}
