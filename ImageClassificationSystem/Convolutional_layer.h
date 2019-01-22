/*
 * Convolutionallayer.h
 *
 *  Created on: Jan 22, 2019
 *      Author: ibrahim
 */

#include <stdlib.h>

#ifndef CONVOLUTIONAL_LAYER_H_
#define CONVOLUTIONAL_LAYER_H_

class Convolutional_layer {
private:
	int n; // number of convolutional layers
	int size;
	int stride;
	Image* kernels; // or filters
	Image* kernel_updates;
	Image output;
	Image upsampled; // inputs
public:
	Convolutional_layer(int w, int h, int c, int n, int size, int stride);
	virtual ~Convolutional_layer();


};

#endif /* CONVOLUTIONAL_LAYER_H_ */
