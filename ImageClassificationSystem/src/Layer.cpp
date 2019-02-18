/*
 * Layer.cpp
 *
 *  Created on: Jan 31, 2019
 *      Author: ibrahim
 */

#include "Layer.h"

Layer::Layer() {

}

void Layer::add_bias(float *output, float *biases, int n, int size) {
	int i, j;

	for (i = 0; i < n; ++i) {
		for (j = 0; j < size; ++j) {
			output[(n + i) * size + j] += biases[i];
		}
	}

}

void Layer::forward_layer(Network *net) {
	printf("Greetings from forward Layer\n");
	return;
}
