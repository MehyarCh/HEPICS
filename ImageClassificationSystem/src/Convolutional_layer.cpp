/*
 * Convolutionl_layer.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: ibrahim
 */

#include "Convolutional_layer.h"

Convolutional_layer::Convolutional_layer() {

}

int Convolutional_layer::convolutional_out_width(Convolutional_layer l) {
	return (l.w + 2 * l.pad - l.size) / l.stride + 1;
}

int Convolutional_layer::convolutional_out_height(Convolutional_layer l) {
	return (l.h + 2 * l.pad - l.size) / l.stride + 1;
}

void add_bias(float *output, float *biases, int batch, int n, int size) {
	int i, j, b;
	for (b = 0; b < batch; ++b) {
		for (i = 0; i < n; ++i) {
			for (j = 0; j < size; ++j) {
				output[(b * n + i) * size + j] += biases[i];
			}
		}
	}
}

void Convolutional_layer::forward_layer(Network *net) {
	float *b = net->getWorkspace();
	float *im =  net->input;
	im2col_cpu(im, this->c, this->h, this->w, this->size, this->stride, this->pad, b);
	//add_bias(this->output, this->biases, this->n, this->out_h * this->out_w);
	Activation activator = Activation();
	activator.activate_array(this->output, this->outputs, this->activation);

}

Convolutional_layer::Convolutional_layer(int h, int w, int c, int n,
		int size, int stride, int padding, Activation::ACTIVATION activation) {
	int i;
	this->type = Layer_Type::LAYER_TYPE::CONVOLUTIONAL;

	this->h = h;
	this->w = w;
	this->c = c;
	this->n = n;

	this->stride = stride;
	this->size = size;
	this->pad = padding;
	//this->biases = (float *) calloc(n, sizeof(float));
	//this->bias_updates = (float *) calloc(n, sizeof(float));

	//this->biases = (float *) calloc(n, sizeof(float));
	//this->bias_updates = (float *) calloc(n, sizeof(float));

	this->nweights = c / n * size * size;
	this->nbiases = n;

	int out_w = convolutional_out_width(*this);
	int out_h = convolutional_out_height(*this);
	this->out_h = out_h;
	this->out_w = out_w;
	this->out_c = n;
	this->outputs = this->out_h * this->out_w * this->out_c;
	this->inputs = this->w * this->h * this->c;

	this->output = (float *) calloc(this->outputs, sizeof(float));


	fprintf(stderr,
			"conv  %5d %2d x%2d /%2d  %4d x%4d x%4d   ->  %4d x%4d x%4d \n",
			n, size, size, stride, w, h, c, this->getOutW(), this->getOutH(),
			this->getOutC());

}

