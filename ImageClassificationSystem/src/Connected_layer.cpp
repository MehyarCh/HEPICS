/*
 * Connected_layer.cpp
 *
 *  Created on: Jan 28, 2019
 *      Author: ibrahim
 */

#include "Connected_layer.h"

Connected_layer::Connected_layer(int inputs, int outputs) {
	int i;
	this->inputs = inputs;
	this->outputs = outputs;

	this->output = (double *) calloc(outputs, sizeof(double));

	this->weight_updates = (double *) calloc(inputs * outputs, sizeof(double));
	this->weights = (double *) calloc(inputs * outputs, sizeof(double));

	for (i = 0; i < inputs * outputs; ++i) {
		this->weights[i] = .5 - (double)rand()/RAND_MAX;
	}

	this->bias_updates = (double *) calloc(outputs, sizeof(double));
	this->biases = (double *) calloc(outputs, sizeof(double));

	for (i = 0; i < outputs; ++i) {
		this->biases[i] = (double)rand()/RAND_MAX;;
	}

}

double connected_activation(double x) {
	return x * (x > 0);
}

void Connected_layer::run_connected_layer(double *input) {
    int i, j;
    for(i = 0; i < this->outputs; ++i){
        this->output[i] = this->biases[i];
        for(j = 0; j < this->inputs; ++j){
            this->output[i] += input[j] * this->weights[i * this->outputs + j];
        }
        this->output[i] = connected_activation(this->output[i]);
}
}

Connected_layer::~Connected_layer() {
	// TODO Auto-generated destructor stub
}


