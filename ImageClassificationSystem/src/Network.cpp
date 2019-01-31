/*
 * Network.cpp
 *
 *  Created on: Jan 28, 2019
 *      Author: ibrahim
 */

#include "Network.h"

Network::Network(int n) {
	this->n = n;
	*this->layers = malloc(sizeof(LAYER_TYPE));
	this->layers = malloc(sizeof(*layers));
}

Network::~Network() {
	// TODO Auto-generated destructor stub
}

void Network::run_network(Image *input, Network net) {
	int i;
	double *input_d = 0;
	for (i = 0; i < net.n; ++i) {
		if (net.types[i] == CONVOLUTIONAL) {
			Convolutional_layer layer = *(Convolutional_layer *)net.layers[i];
			layer.run_convolutional_layer(input);
			input = layer.output; // output is the input of the next layer
			input_d = layer.output->data; // output data is the input data of the next layer
		}
		else if (net.types[i] ==  CONNECTED) {
			Connected_layer layer = *(Connected_layer *)net.layers[i];
			layer.run_connected_layer(input_d);
			// THERE IS NO OUTPUT IMAGE DELIVERED BY CONNECTED LAYER
			input_d = layer.output;
		}
		else if (net.types[i] == MAXPOOL) {
			Maxpool_layer layer = *(Maxpool_layer *)net.types[i];
			layer.run_maxpool_layer(input);
			input = layer.output; // output is the input of the next layer
			input_d = layer.output->data; // output data is the input data of the next layer
		}
		else if (net.types[i] == SOFTMAX) {
			Softmax_layer layer = *(Softmax_layer *)net.types[i];
			layer.run_softmax_layer(input_d);
			input = layer.output; // output is the input of the next layer
			//input_d = layer.output->data; // DIDN'T LOOK AT IT YET!!
		}
	}
}

//getters
void** Network::getLayers() const {
	return layers;
}
int Network::getN() const {
	return n;
}

//setters
void Network::setLayers(void** layers) {
	this->layers = layers;
}
void Network::setN(int n) {
	this->n = n;
}
void Network::setTypes(LAYER_TYPE* types) {
	this->types = types;
}


Image Network::get_network_image_layer(Network net) {
	int i;
	for (i = net.n - 1; i >= 0; --i) {
		if (net.types[i] == CONVOLUTIONAL) {
			Convolutional_layer layer = *(Convolutional_layer *)net.layers[i];
			return *layer.output;
		}
		else if (net.types[i] == MAXPOOL) {
			Maxpool_layer layer = *(Maxpool_layer *)net.layers[i];
			return *layer.output;
		}
	}
	return Image(1,1,1);
}


