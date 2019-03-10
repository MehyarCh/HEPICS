#include <gtest/gtest.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdint>
#include <memory>
#include <assert.h>
#include <cmath>
#include "hepics/Image.h"
#include "hepics/Local_response_normalization_layer.h"
using namespace std;
using namespace hepics;
using std::unique_ptr;

auto lrn = make_unique<Local_response_normalization_layer>();
auto inputImage = make_unique<Image>(2, 2, 2, 1);
auto expectOutput = make_unique<Image>(2, 2, 2, 1);

void setData() {
	for (int c = 0; c < 2; ++c) {
		for (int y = 0; y < 2; ++y) {
			for (int x = 0; x < 2; ++x) {
				inputImage->at(x, y, c, 0) = 50 * sqrt(2);
			}
		}
	}

	for (int c = 0; c < 2; ++c) {
			for (int y = 0; y < 2; ++y) {
				for (int x = 0; x < 2; ++x) {
					expectOutput->at(x, y, c, 0) = 50 * sqrt(2) / pow(1.2, 0.75);
				}
			}
		}
}

TEST(local_response_normalization_layer, test_local_response_normalization_layer) {
	setData();
	auto output = lrn->forward_layer(*inputImage);
	for (int c = 0; c < 2; ++c) {
		for (int y = 0; y < 2; ++y) {
			for (int x = 0; x < 2; ++x) {
				//cerr << output->at(x, y, c, 0) << "\n";
				ASSERT_EQ(output->at(x, y, c, 0), expectOutput->at(x, y, c, 0));
			}
		}
	}
}
