/*
 * Network.h
 *
 *  Created on: Jan 28, 2019
 *      Author: ibrahim
 */

#ifndef SRC_NETWORK_H_
#define SRC_NETWORK_H_

#include <stdlib.h>
#include "Layer.h"
#include "Convolutional_layer.h"
#include "Connected_layer.h"
#include "Maxpool_layer.h"
#include "Softmax_layer.h"
#include "BLAS.h" // EXTERNAL LIBRARY from Caffe
#include <vector>
using namespace std;

class Parser;

class Network {
private:
	int n;
	int h; // input height
	int w; // input width
	int c; // input channels
    //int inputs;
    //int outputs;
	int batch;

	float *output;
	int index;
	vector<Layer> layers;

public:
	float *workspace; // USED BY EXTERNAL LIBRARY: REFER TO "forward_convolutional_layer()" METHOD
	float *delta;
	//Layer **layers; // declared public for now just to get around problem in parse_networ_cfg
	float *input;

	Network(int number_of_layers);

	Layer get_network_output_layer();
	void forward_network();
	float *network_predict(float *input);

	int getBatch() {
		return batch;
	}

	void setBatch(int batch) {
		this->batch = batch;
	}

	int getN() {
		return n;
	}

	void setN(int n) {
		this->n = n;
	}

	void setInput(float* input) {
		this->input = input;
	}

	float* getWorkspace() {
		return workspace;
	}

	void setWorkspace(float* workspace) {
		this->workspace = workspace;
	}

	int getC() const {
		return c;
	}

	void setC(int c) {
		this->c = c;
	}

	int getH() const {
		return h;
	}

	void setH(int h) {
		this->h = h;
	}

	int getW() const {
		return w;
	}

	void setW(int w) {
		this->w = w;
	}

	float* getInput() {
		return input;
	}

	/*int getInputs() {
		return inputs;
	}

	void setInputs(int inputs) {
		this->inputs = inputs;
	}*/

	/*int getOutputs() {
		return outputs;
	}

	void setOutputs(int outputs) {
		this->outputs = outputs;
	}*/

	float* getOutput() {
		return output;
	}

	void setOutput(float* output) {
		this->output = output;
	}

	vector<Layer> getLayers();
};

#endif /* SRC_NETWORK_H_ */
