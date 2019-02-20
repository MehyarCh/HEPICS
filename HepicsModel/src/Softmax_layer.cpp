/*
 * Softmax_layer.cpp
 *
 *  Created on: Jan 28, 2019
 *      Author: ibrahim
 */

#include "Softmax_layer.h"

Softmax_layer::Softmax_layer() {

}

Softmax_layer::Softmax_layer(int inputs) {
    fprintf(stderr, "softmax                                        %4d\n",  inputs);
    this->type = Layer_Type::SOFTMAX;
    this->inputs = inputs;
    this->outputs = inputs;
    this->output = (float *)calloc(inputs, sizeof(float));


}

void Softmax_layer::forward_layer(Network *net) {
	printf("Greetings from forward Softmax Layer\n");
	return;
}

void Softmax_layer::copy_layer(Layer *l) {
	this->activation = l->activation;
	this->biases = l->biases;
	this->h = l->h;
	this->w = l->w;
	this->c = l->c;
	this->n = l->n;
	this->nweights = l->nweights;
}
