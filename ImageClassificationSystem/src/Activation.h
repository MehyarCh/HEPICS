/*
 * Activation.h
 *
 *  Created on: Jan 31, 2019
 *      Author: ibrahim
 */

#ifndef SRC_ACTIVATION_H_
#define SRC_ACTIVATION_H_

#include <math.h>
#include <string.h>
#include <stdio.h>

class Activation {
	typedef enum {
		SIGMOID,
		RELU,
		IDENTITY,
		RAMP
	} ACTIVATION;

	double activate(double x, ACTIVATION a);
	ACTIVATION get_activation(char *s);
};

#endif /* SRC_ACTIVATION_H_ */
