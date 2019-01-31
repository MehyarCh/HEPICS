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
private:
	int n; // number of convolutional layers
	int stride;
	Image *kernels; // or filters
	Image *kernel_updates;
	Image *output;
	Image *upsampled; // inputs
public:

	Convolutional_layer(int w, int h, int c, int n, int size, int stride);
	virtual ~Convolutional_layer();

	void run_convolutional_layer(Image *input);

	//getters
	const Image*& getKernelUpdates() const;
	const Image*& getKernels() const;
	int getN() const;
	const Image*& getOutput() const;
	int getStride() const;
	const Image*& getUpsampled() const;

	//setters
	void setKernels(const Image*& kernels);
	void setKernelUpdates(const Image*& kernelUpdates);
	void setN(int n);
	void setOutput(const Image*& output);
	void setStride(int stride);
	void setUpsampled(const Image*& upsampled);
};

#endif /* CONVOLUTIONAL_LAYER_H_ */
