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
	this->kernels = (Image *) calloc(n, sizeof(Image));
	this->kernel_updates = (Image *) calloc(n, sizeof(Image));

	// Initialize filters
	for (i = 0; i < n; ++i) {
		//this->kernels[i] = NULL; // make_random_kernel(size, c);
		//this->kernel_updates[i] = NULL; // make_random_kernel(size, c);
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
void Convolutional_layer::run_convolutional_layer(Image *input) {
	int i;
	for (i = 0; i < this->n; ++i) {
		input->convolve(&this->kernels[i], this->stride, i, *output); // Very strange here: dereferencing layer.kernels[i] which has type "Image"
	}
	for (i = 0; i < input->height * input->width * input->channels; ++i) {
		input->data[i] = convolution_activation(input->data[i]);
	}
}

//getters
const Image*& Convolutional_layer::getKernelUpdates() const {
	return kernel_updates;
}
const Image*& Convolutional_layer::getKernels() const {
	return kernels;
}
int Convolutional_layer::getN() const {
	return n;
}
const Image*& Convolutional_layer::getOutput() const {
	return output;
}
int Convolutional_layer::getStride() const {
	return stride;
}
const Image*& Convolutional_layer::getUpsampled() const {
	return upsampled;
}

//setters
void Convolutional_layer::setKernelUpdates(const Image*& kernelUpdates) {
	kernel_updates = kernelUpdates;
}
void Convolutional_layer::setKernels(const Image*& kernels) {
	this->kernels = kernels;
}
void Convolutional_layer::setN(int n) {
	this->n = n;
}
void Convolutional_layer::setOutput(const Image*& output) {
	this->output = output;
}
void Convolutional_layer::setStride(int stride) {
	this->stride = stride;
}
void Convolutional_layer::setUpsampled(const Image*& upsampled) {
	this->upsampled = upsampled;
}

