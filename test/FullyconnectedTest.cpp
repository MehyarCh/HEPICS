#include <gtest/gtest.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdint>
#include <memory>
#include <assert.h>
#include <cmath>
#include "../hepics/Image.h"
#include "../hepics/Fully_connected_layer.h"
using namespace std;
using namespace hepics;
using std::unique_ptr;

auto setWeights() {
	auto weights = make_unique<Image>(4, 4, 1, 1);
	int counter = 1;
	for (int y = 0; y < weights->height; y++) {
		for (int x = 0; x < weights->width; x++) {
			weights->at(x, y, 0, 0) = counter;
			counter++;
		}
	}
	return weights;
}

TEST(fully_connected_layer, test_fully_connected_layer) {
	auto weights = setWeights();
	auto bias = vector<float> {1, 0, 1, 0};

	auto fully_connected_layer = make_unique<Fully_connected_layer>(*weights, move(bias));
	auto inputImage = make_unique<Image>(2, 2, 1, 1);
	inputImage->at(0, 0, 0, 0) = 1;
	inputImage->at(1, 0, 0, 0) = 2;
	inputImage->at(0, 1, 0, 0) = 3;
	inputImage->at(1, 1, 0, 0) = 4;

	auto expectedOutput = make_unique<Image>(1, 1, 4, 1);
	expectedOutput->at(0, 0, 0, 0) = 31;
	expectedOutput->at(0, 0, 1, 0) = 70;
	expectedOutput->at(0, 0, 2, 0) = 111;
	expectedOutput->at(0, 0, 3, 0) = 150;

	auto outputFrom_Fully_connected_layer =
			fully_connected_layer->forward_layer(*inputImage);

	for (int i = 0; i < 4; i++) {
		//cerr << outputFrom_Fully_connected_layer->at(0, 0, i, 0) << "\n";
		ASSERT_EQ(outputFrom_Fully_connected_layer->at(0, 0, i, 0),
			expectedOutput->at(0, 0, i, 0));
	}
}



