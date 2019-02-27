#include "Image.h"
#include <gtest/gtest.h>

using namespace hepics;

Image *input_image;
Image *second_input;

void test_constructor(){
	second_input= new Image(227,226,3);
}

void test_load_image(){
	input_image= new Image(227,227,3);
	input_image->load_image("/home/mehyar/localRepository/hepics/new_hepics/test/Pictures/dog.jpeg");
}


TEST(constructor, test_constructor) {
	test_constructor();
	ASSERT_EQ(second_input->height,226);
	ASSERT_EQ(second_input->width,227);
	ASSERT_EQ(second_input->channels,3);
}

TEST(load, test_load_image) {
	test_load_image();
	ASSERT_EQ(input_image->height,227);
	ASSERT_EQ(input_image->width,227);
	ASSERT_EQ(input_image->channels,3);
}
