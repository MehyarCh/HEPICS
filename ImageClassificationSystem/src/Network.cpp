/*
 * Network.cpp
 *
 *  Created on: Jan 28, 2019
 *      Author: ibrahim
 */

#include "Network.h"

Network* Network::make_network(int n) {
    Network *net = (Network *)calloc(1, sizeof(Network));
    net->n = n;
    net->layers = new Layer*[net->n];
    return net;
}

Layer Network::get_network_output_layer() {
	return *this->layers[n - 1];
}

void Network::forward_network() {
	Network *net = this;
	//net.layers = net.layers - 4;
	for (int i = 0; i < n; ++i) {
		net->layers[i]->forward_layer(net);
		//net->input = l->getOutput();
	}
}

float* Network::network_predict(float *input) {
    Network orig = *this;
    this->input = input;
    this->delta = 0;
    this->forward_network();
    float *out = this->output;
    *this = orig;
    return out;
}

