#include "Image.h"
#include <gtest/gtest.h>

using namespace hepics;

Image *input_image= new Image(0,0,0);

void test_constructor(){

}

void test_load_image(){

}


TEST(constructor, test_constructor) {
	ASSERT_EQ(0,0);
	ASSERT_EQ(0,0);
	ASSERT_EQ(0,0);
}
