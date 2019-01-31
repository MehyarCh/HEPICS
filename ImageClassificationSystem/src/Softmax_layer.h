/*
 * Softmaxl_ayer.h
 *
 *  Created on: Jan 31, 2019
 *      Author: ibrahim
 */

#ifndef SOFTMAXL_AYER_H_
#define SOFTMAXL_AYER_H_

#include <math.h>

class Softmax_layer {
public:
	int inputs;
	double *delta;
	double *output;

	Softmax_layer(int inputs);
	void run_softmax_layer(double *input);

};

#endif /* SOFTMAXL_AYER_H_ */
