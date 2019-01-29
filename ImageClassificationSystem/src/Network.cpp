/*
 * Network.cpp
 *
 *  Created on: Jan 28, 2019
 *      Author: ibrahim
 */

#include "Network.h"

Network::Network() {
	// TODO Auto-generated constructor stub

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
	}
}

Image Network::get_network_image(Network net) {

	int i;
	for (i = net.n - 1; i >= 0; --i) {
		if (net.types[i] == CONVOLUTIONAL) {
			Convolutional_layer layer = *(Convolutional_layer *)net.layers[i];
			return *layer.output;
		}
		else if (net.types[i] == CONNECTED) {
			Connected_layer layer = *(Connected_layer *)net.layers[i];
			// return *layer.output; // doesn't work output is pointer to double
			return Image(1,1,1); // PLACEHOLDER
		}
		else if (net.types[i] == MAXPOOL) {
			Maxpool_layer layer = *(Maxpool_layer *)net.layers[i];
			return *layer.output;
		}
	}
	return Image(1,1,1);
}

