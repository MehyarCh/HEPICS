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
private:
	int inputs;
	double *delta;
	double *output;

public:

	Softmax_layer(int inputs);
	void run_softmax_layer(double *input);

	//getters
	double* getDelta() const;
	int getInputs() const;
	double* getOutput() const;

	//setters
	void setDelta(double* delta);
	void setInputs(int inputs);
	void setOutput(double* output);
};

#endif /* SOFTMAXL_AYER_H_ */
