/*
 * Fully_connected_layer_Test.cpp
 *
 *  Created on: Feb 25, 2019
 *      Author: bahaa
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
#include "Fully_connected_layer.h"
using namespace std;
using namespace hepics;
using std::unique_ptr;

auto weights = make_unique<Image>(4, 4, 1);
void setWeights() {
	int counter = 1;
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			weights->at(x, y, 0) = counter;
			counter++;
		}
	}
}

TEST(fully_connected_layer, test_fully_connected_layer) {
	setWeights();

	auto fully_connected_layer = make_unique<Fully_connected_layer>(*weights);
	auto inputImage = make_unique<Image>(2, 2, 1); //input s=....
	inputImage->at(0, 0, 0) = 1;
	inputImage->at(1, 0, 0) = 2;
	inputImage->at(0, 1, 0) = 3;
	inputImage->at(1, 1, 0) = 4;

	auto expectedOutput = make_unique<Image>(1, 4, 1); //yx1.....
	expectedOutput->at(0, 0, 0) = 90;
	expectedOutput->at(0, 1, 0) = 100;
	expectedOutput->at(0, 2, 0) = 110;
	expectedOutput->at(0, 3, 0) = 120;

	auto outputFrom_Fully_connected_layer =
			fully_connected_layer->forward_layer(*inputImage);

	for (int i = 0; i < 4; i++) {
		cerr << outputFrom_Fully_connected_layer->at(0, i, 0);
		ASSERT_EQ(outputFrom_Fully_connected_layer->at(0, i, 0),
				expectedOutput->at(0, i, 0));
	}
}



