/*
 * Connected_layer.cpp
 *
 *  Created on: Jan 28, 2019
 *      Author: ibrahim
 */

#include "Connected_layer.h"

Connected_layer::Connected_layer() {

}

void Connected_layer::forward_layer(Network *net) {

	add_bias(this->output, this->biases, this->outputs, 1);
	Activation activator = Activation();
	activator.activate_array(this->output, this->outputs, this->activation);
}

Connected_layer::Connected_layer(int inputs, int outputs,
		Activation::ACTIVATION activation, int batch_normalize) {
	int i;
	this->type = Layer_Type::CONNECTED;

	this->inputs = inputs;
	this->outputs = outputs;
	this->batch_normalize = batch_normalize;
	this->h = 1;
	this->w = 1;
	this->c = inputs;
	this->out_h = 1;
	this->out_w = 1;
	this->out_c = outputs;

	this->output = (float *) calloc(outputs, sizeof(float));
	//this->delta = (float *) calloc(outputs, sizeof(float));

	this->weight_updates = (float *) calloc(inputs * outputs, sizeof(float));
	this->bias_updates = (float *) calloc(outputs, sizeof(float));

	this->weights = (float *) calloc(outputs * inputs, sizeof(float));
	this->biases = (float *) calloc(outputs, sizeof(float));

	//this->backward = backward_connected_layer;
	//this->update = update_connected_layer;

	//float scale = 1./sqrt(inputs);
	float scale = sqrt(2. / inputs);
	for (i = 0; i < outputs * inputs; ++i) {
		this->weights[i] = scale * Utils::rand_uniform(-1, 1);
	}

	for (i = 0; i < outputs; ++i) {
		this->biases[i] = 0;
	}
	if (batch_normalize) {
		this->scales = (float *) calloc(outputs, sizeof(float));
		this->scale_updates = (float *) calloc(outputs, sizeof(float));
		for (i = 0; i < outputs; ++i) {
			this->scales[i] = 1;
		}

	}

	this->activation = activation;
	fprintf(stderr, "connected                            %4d  ->  %4d\n",
			inputs, outputs);

}
