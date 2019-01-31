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
private:
	int inputs;
	int outputs;
	double *weights;
	double *biases;
	double *weight_updates;
	double *bias_updates;
	double *output; // outputs by connected layers are not images
public:
	Connected_layer(int inputs, int outputs);
	virtual ~Connected_layer();
	void run_connected_layer(double *input);

	double* getBiasUpdates() const;
	double* getBiases() const;
	int getInputs() const;
	double* getOutput() const;
	int getOutputs() const;
	double* getWeightUpdates() const;
	double* getWeights() const;

	void setBiasUpdates(double* biasUpdates);
	void setBiases(double* biases);
	void setInputs(int inputs);
	void setOutput(double* output);
	void setOutputs(int outputs);
	void setWeightUpdates(double* weightUpdates);
	void setWeights(double* weights);
};

#endif /* CONNECTED_LAYER_H_ */
