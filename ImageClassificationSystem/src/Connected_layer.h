/*
 * Connected_layer.h
 *
 *  Created on: Jan 28, 2019
 *      Author: ibrahim
 */

#ifndef SRC_CONNECTED_LAYER_H_
#define SRC_CONNECTED_LAYER_H_

#include "Layer.h"
#include "Layer_Type.h"
#include "Activation.h"
#include "Utils.h"
#include "Network.h"
#include "IM2COL.h" // EXTERNAL LIBRARY from Caffe
#include "BLAS.h" // EXTERNAL LIBRARY from Caffe
#include "GEMM.h" // EXTERNAL LIBRARY from Caffe

class Connected_layer: public Layer {
public:
	Connected_layer();
	Connected_layer(int inputs, int outputs, Activation::ACTIVATION activation);
	void forward_layer(Network *net);
};

#endif /* SRC_CONNECTED_LAYER_H_ */
