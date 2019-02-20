/*
 * Convolutionl_layer.h
 *
 *  Created on: Jan 22, 2019
 *      Author: ibrahim
 */

#ifndef SRC_CONVOLUTIONAL_LAYER_H_
#define SRC_CONVOLUTIONAL_LAYER_H_

#include <stdlib.h>
#include "Layer.h"
#include "Utils.h"
#include "Network.h"
#include "Activation.h"
#include "IM2COL.h" // EXTERNAL LIBRARY from Caffe
#include "BLAS.h" // EXTERNAL LIBRARY from Caffe
#include "GEMM.h" // EXTERNAL LIBRARY from Caffe

class Convolutional_layer: public Layer {
public:
	Convolutional_layer();
	Convolutional_layer(int h, int w, int c, int n, int size, int stride, int padding, Activation::ACTIVATION activation);

	int convolutional_out_width(Convolutional_layer l);
	int convolutional_out_height(Convolutional_layer l);
	void forward_layer(Network *net);

};

#endif /* SRC_CONVOLUTIONAL_LAYER_H_ */
