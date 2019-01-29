/*
 * Maxpool_layer.h
 *
 *  Created on: Jan 28, 2019
 *      Author: ibrahim
 */

#ifndef MAXPOOL_LAYER_H_
#define MAXPOOL_LAYER_H_

#include "Image.h"

class Maxpool_layer {
public:
	int stride;
	Image *output;

	Maxpool_layer(int h, int w, int c, int stride);
	virtual ~Maxpool_layer();
	void run_maxpool_layer(Image *input);
};

#endif /* MAXPOOL_LAYER_H_ */
