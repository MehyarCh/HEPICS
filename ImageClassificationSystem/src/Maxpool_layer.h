/*
 * Maxpool_layer.h
 *
 *  Created on: Jan 28, 2019
 *      Author: ibrahim
 */

#ifndef SRC_MAXPOOL_LAYER_H_
#define SRC_MAXPOOL_LAYER_H_

#include "Network.h"
#include "Layer.h"

class Maxpool_layer: public Layer {
private:

public:
	Maxpool_layer();
	Maxpool_layer(int batch, int h, int w, int c, int size, int stride, int padding);
	void forward_layer(Network *net);
	void copy_layer(Layer *l);
};

#endif /* SRC_MAXPOOL_LAYER_H_ */
