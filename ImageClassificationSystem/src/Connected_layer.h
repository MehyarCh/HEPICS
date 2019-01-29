/*
 * Connected_layer.h
 *
 *  Created on: Jan 28, 2019
 *      Author: ibrahim
 */

#ifndef CONNECTED_LAYER_H_
#define CONNECTED_LAYER_H_

#include <stdlib.h>

class Connected_layer {
public:
	int inputs;
	int outputs;
	double *weights;
	double *biases;
	double *weight_updates;
	double *bias_updates;
	double *output; // outputs by connected layers are not images

	Connected_layer(int inputs, int outputs);
	virtual ~Connected_layer();
	void run_connected_layer(double *input);
};

#endif /* CONNECTED_LAYER_H_ */
