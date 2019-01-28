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

	this->output = new Image((h - 1) / stride + 1, (w - 1) / stride +1, n);
	this->upsampled = new Image(h, w, c); // new Image(h, w, n);
}

Convolutional_layer::~Convolutional_layer() {
	// TODO Auto-generated destructor stub
}

double convolution_activation(double x) {
	return x * (x > 0);
}

void Convolutional_layer::run_convolutional_layer(Image input, const Convolutional_layer layer) {
	int i;
	for (i = 0; i < layer.n; ++i) {
		input.convolve(layer.kernels[i], layer.stride, i, layer.output); // Very strange here: dereferencing layer.kernels[i] which has type "Image"
	}
	for (i =0; i < input.height * input.width * input.channels; ++i) {
		input.data[i] = convolution_activation(input.data[i]);
	}
}
