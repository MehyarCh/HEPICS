#include <gtest/gtest.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdint>
#include <memory>
#include <assert.h>
#include <cmath>
#include "Image.h"
#include "Maxpool_layer.h"
using namespace std;
using namespace hepics;
using std::unique_ptr;

auto mxp = make_unique<Maxpool_layer>();

auto input = make_unique<Image>(3, 3, 2, 1);
auto expectedOutput = make_unique<Image>(2, 2, 2, 1);
auto input2 = make_unique<Image>(6, 6, 2, 1);
auto expectedOutput2 = make_unique<Image>(3, 3, 2, 1);

void setImageData() {
	float counter = 1;
	for (int c = 0; c < 2; ++c) {
		for (int y = 0; y < 3; ++y) {
			for (int x = 0; x < 3; ++x) {
				input->at(x, y, c, 0) = counter;
				counter++;
			}
		}
	}
	expectedOutput->at(0, 0, 0, 0) = 5;
	expectedOutput->at(1, 0, 0, 0) = 6;
	expectedOutput->at(0, 1, 0, 0) = 8;
	expectedOutput->at(1, 1, 0, 0) = 9;
	expectedOutput->at(0, 0, 1, 0) = 14;
	expectedOutput->at(1, 0, 1, 0) = 15;
	expectedOutput->at(0, 1, 1, 0) = 17;
	expectedOutput->at(1, 1, 1, 0) = 18;
}

void setImageData2() {
	float counter = 1;
	for (int c = 0; c < 2; ++c) {
		for (int y = 0; y < 6; ++y) {
			for (int x = 0; x < 6; ++x) {
				input2->at(x, y, c, 0) = counter;
				counter++;
			}
		}
	}
	expectedOutput2->at(0, 0, 0, 0) = 8;
	expectedOutput2->at(1, 0, 0, 0) = 10;
	expectedOutput2->at(2, 0, 0, 0) = 12;
	expectedOutput2->at(0, 1, 0, 0) = 20;
	expectedOutput2->at(1, 1, 0, 0) = 22;
	expectedOutput2->at(2, 1, 0, 0) = 24;
	expectedOutput2->at(0, 2, 0, 0) = 32;
	expectedOutput2->at(1, 2, 0, 0) = 34;
	expectedOutput2->at(2, 2, 0, 0) = 36;

	expectedOutput2->at(0, 0, 1, 0) = 44;
	expectedOutput2->at(1, 0, 1, 0) = 46;
	expectedOutput2->at(2, 0, 1, 0) = 48;
	expectedOutput2->at(0, 1, 1, 0) = 56;
	expectedOutput2->at(1, 1, 1, 0) = 58;
	expectedOutput2->at(2, 1, 1, 0) = 60;
	expectedOutput2->at(0, 2, 1, 0) = 68;
	expectedOutput2->at(1, 2, 1, 0) = 70;
	expectedOutput2->at(2, 2, 1, 0) = 72;
}

TEST(max_pool_layer, test_max_pool) {
	setImageData();
	auto newOutput = mxp->forward_layer(*input);
	for (int c = 0; c < 2; ++c) {
		for (int y = 0; y < 2; ++y) {
			for (int x = 0; x < 2; ++x) {
				//cerr << newOutput->at(x, y, c) << "\n";
				ASSERT_EQ(newOutput->at(x, y, c, 0), expectedOutput->at(x, y, c, 0));
			}
		}
	}

}

TEST(max_pool_layer2, test_max_pool2) {
	setImageData2();
	auto newOutput2 = mxp->forward_layer(*input2);
	for (int c = 0; c < 2; ++c) {
		for (int y = 0; y < newOutput2->height; ++y) {
			for (int x = 0; x < newOutput2->width; ++x) {
				//cerr << newOutput2->at(x, y, c) << "\n";
				ASSERT_EQ(newOutput2->at(x, y, c, 0), expectedOutput2->at(x, y, c, 0));
			}
		}
	}
}

