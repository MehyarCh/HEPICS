/*
 * Lrn_layer_test.cpp
 *
 *  Created on: Feb 27, 2019
 *      Author: Linjuan
 */
#include <gtest/gtest.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdint>
#include <memory>
#include <assert.h>
#include <cmath>
#include "Image.h"
#include "Local_response_normalization_layer.h"
using namespace std;
using namespace hepics;
using std::unique_ptr;

auto lrn = make_unique<Local_response_normalization_layer>();
auto input = make_unique<Image>(2, 2, 2);
auto expectedOutput = make_unique<Image>(2, 2, 2);

void setImageData() {
	for (int c = 0; c < 2; ++c) {
		for (int y = 0; y < 2; ++y) {
			for (int x = 0; x < 2; ++x) {
				input->at(x, y, c) = 100;
			}
		}
	}

	for (int c = 0; c < 2; ++c) {
			for (int y = 0; y < 2; ++y) {
				for (int x = 0; x < 2; ++x) {
					expectedOutput->at(x, y, c) = 1;
				}
			}
		}
}

TEST(local_response_normalization_layer, test_local_response_normalization_layer) {
	setImageData();
	auto newOutput = lrn->forward_layer(*input);
	for (int c = 0; c < 2; ++c) {
		for (int y = 0; y < 2; ++y) {
			for (int x = 0; x < 2; ++x) {
				//cerr << newOutput->at(x, y, c) << "\n";
				ASSERT_EQ(newOutput->at(x, y, c), expectedOutput->at(x, y, c));
			}
		}
	}
}



