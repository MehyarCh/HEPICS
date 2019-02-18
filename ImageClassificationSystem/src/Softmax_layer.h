/*
 * Softmax_layer.h
 *
 *  Created on: Jan 28, 2019
 *      Author: ibrahim
 */

#ifndef SRC_SOFTMAX_LAYER_H_
#define SRC_SOFTMAX_LAYER_H_

#include "Network.h"
#include "Layer.h"

class Softmax_layer: public Layer {
public:
	Softmax_layer();
	Softmax_layer(int inputs);
	void copy_layer(Layer *l);
	void forward_layer(Network *net);

};

#endif /* SRC_SOFTMAX_LAYER_H_ */
