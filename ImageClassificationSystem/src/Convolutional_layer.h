/*
 * Convolutionallayer.h
 *
 *  Created on: Jan 22, 2019
 *      Author: ibrahim
 */


#ifndef CONVOLUTIONAL_LAYER_H_
#define CONVOLUTIONAL_LAYER_H_

#include "Image.h"

class Convolutional_layer {
public:
	int n; // number of convolutional layers
	int stride;
	Image *kernels; // or filters
	Image *kernel_updates;
	Image *output;
	Image *upsampled; // inputs

	Convolutional_layer(int w, int h, int c, int n, int size, int stride);
	virtual ~Convolutional_layer();
	void run_convolutional_layer(Image *input);


};

#endif /* CONVOLUTIONAL_LAYER_H_ */
