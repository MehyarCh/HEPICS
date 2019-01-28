/*
 * Connected_layer.cpp
 *
 *  Created on: Jan 28, 2019
 *      Author: ibrahim
 */

#include "Connected_layer.h"

Connected_layer::Connected_layer(int inputs, int outputs) {
	int i;
	Connected_layer layer;
	this->inputs = inputs;
	this->outputs = outputs;

	this->output = calloc(outputs, sizeof(double*));

	this->weight_updates = calloc(inputs * outputs, sizeof(double));
	this->weights = calloc(inputs * outputs, sizeof(double));

	for (i = 0; i < inputs * outputs; ++i) {
		this->weights[i] = .5 - (double)rand()/RAND_MAX;
	}

	this->bias_updates = calloc(outputs, sizeof(double));
	this->biases = calloc(outputs, sizeof(double));

	for (i = 0; i < outputs; ++i) {
		this->biases[i] = (double)rand()/RAND_MAX;;
	}

}

double connected_activation(double x) {
	return x * (x > 0);
}

void Connected_layer::run_connected_layer(double *input, Connected_layer layer) {
    int i, j;
    for(i = 0; i < layer.outputs; ++i){
        layer.output[i] = layer.biases[i];
        for(j = 0; j < layer.inputs; ++j){
            layer.output[i] += input[j] * layer.weights[i * layer.outputs + j];
        }
        layer.output[i] = connected_activation(layer.output[i]);
}
}

Connected_layer::~Connected_layer() {
	// TODO Auto-generated destructor stub
}


