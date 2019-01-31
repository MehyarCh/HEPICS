/*
 * Activation.cpp
 *
 *  Created on: Jan 31, 2019
 *      Author: ibrahim
 */

#include "Activation.h"

double identity_activation(double x) {
	return x;
}

double sigmoid_activation(double x) {
	return 1./(1. + exp(-x));
}

double relu_activation(double x) {
	return x * (x > 0);
}

double ramp_activation(double x) {
	return x * (x > 0) + .1 * x;
}

double Activation::activate(double x, ACTIVATION a) {
	switch(a) {
	case IDENTITY:
		return identity_activation(x);
	case SIGMOID:
		return sigmoid_activation(x);
	case RELU:
		return relu_activation(x);
	case RAMP:
		return ramp_activation(x);
	}
	return 0;
}

Activation::ACTIVATION Activation::get_activation(char* s) {
	if (strcmp(s, "sigmoid") == 0) return SIGMOID;
	if (strcmp(s, "relu") == 0) return RELU;
	if (strcmp(s, "identity") == 0) return IDENTITY;
	if (strcmp(s, "ramp") == 0) return RAMP;
	fprintf(stderr, "Couldn't find activation %s, going with ReLu\n", s);
	return RELU;
}

