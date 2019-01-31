/*
 * Softmax_layer.cpp
 *
 *  Created on: Jan 31, 2019
 *      Author: ibrahim
 */

#include "Softmax_layer.h"

Softmax_layer::Softmax_layer(int inputs) {
	this->inputs = inputs;
	this->output = calloc(inputs, sizeof(double));
	this->delta = calloc(inputs, sizeof(double));
}

void Softmax_layer::run_softmax_layer(double *input)
{
    int i;
    double sum = 0;
    for(i = 0; i < inputs; ++i){
        sum += exp(input[i]);
    }
    for(i = 0; i < inputs; ++i){
        output[i] = exp(input[i])/sum;
    }
}

