/*
 * Convolutionallayer.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: ibrahim
 */

#include "Convolutional_layer.h"

Convolutional_layer::Convolutional_layer(int w, int h, int c, int n, int size, int stride) {
	int i;
	this->n = n;
	this->stride = stride;
	this->kernels = calloc(n, sizeof(Image));
	this->kernel_updates = calloc(n, sizeof(Image));

	// Initialize filters
	for (i = 0; i < n; ++i) {
		this->kernels[i] = NULL; // make_random_kernel(size, c);
		this->kernel_updates[i] = NULL; // make_random_kernel(size, c);
	}

	this->output = NULL; // new Image((h - 1) / stride + 1), (w - 1) / stride + 1, n);
	this->upsampled = new Image(h, w, c); // new Image(h, w, n);
}

Convolutional_layer::~Convolutional_layer() {
	// TODO Auto-generated destructor stub
}

