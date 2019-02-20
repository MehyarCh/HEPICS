/*
 * Layer.h
 *
 *  Created on: Jan 31, 2019
 *      Author: ibrahim
 */

#ifndef SRC_LAYER_H_
#define SRC_LAYER_H_

#include <stddef.h>
#include "Layer_Type.h"
#include "Activation.h"
class Network; // forward declaration, avoid circular dependency

class Layer {
public:

	Layer();
	//copy_layer();
	Layer_Type::LAYER_TYPE type;
	Activation::ACTIVATION activation;

	int inputs;
	int outputs;
	int nweights;
	int nbiases;
	int h, w, c;
	int out_h, out_w, out_c;
	int n;
	int size;
	int side;
	int stride;
	int spatial;
	int pad;
	int index;
	int   *indexes;

	float * biases;
	float * bias_updates;

	float * scale;

	float * weights;
	float * weight_updates;

	//float * delta;
	float * output;


	size_t workspace_size;
public:

	virtual void forward_layer(Network *net);

	size_t getWorkspaceSize() {
		return workspace_size;
	}

	void setWorkspaceSize(size_t workspaceSize) {
		workspace_size = workspaceSize;
	}

	int getOutC() {
		return out_c;
	}

	void setOutC(int outC) {
		out_c = outC;
	}

	int getOutH() {
		return out_h;
	}

	void setOutH(int outH) {
		out_h = outH;
	}

	int getOutW() {
		return out_w;
	}

	void setOutW(int outW) {
		out_w = outW;
	}

	int getOutputs() {
		return outputs;
	}

	void setOutputs(int outputs) {
		this->outputs = outputs;
	}

	float* getOutput() {
		return output;
	}

	void setOutput(float* output) {
		this->output = output;
	}

	int getN() {
		return n;
	}

	void setN(int n) {
		this->n = n;
	}

	int getSize() {
		return size;
	}

	void setSize(int size) {
		this->size = size;
	}

	int getC() {
		return c;
	}

	void setC(int c) {
		this->c = c;
	}

	int getW() {
		return w;
	}

	void setW(int w) {
		this->w = w;
	}

	int getH() {
		return h;
	}

	void setH(int h) {
		this->h = h;
	}

	Layer_Type::LAYER_TYPE getType() {
		return type;
	}

	void setType(Layer_Type::LAYER_TYPE type) {
		this->type = type;
	}

	Activation::ACTIVATION getActivation() {
		return activation;
	}

	void setActivation(Activation::ACTIVATION activation) {
		this->activation = activation;
	}

	int getNweights() {
		return nweights;
	}

	void setNweights(int nweights) {
		this->nweights = nweights;
	}

	float* getWeights()  {
		return weights;
	}

	void setWeights(float* weights) {
		this->weights = weights;
	}

	static void add_bias(float *output, float *biases, int n, int size);
};

#endif /* SRC_LAYER_H_ */
