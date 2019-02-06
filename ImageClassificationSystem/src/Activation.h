/*
 * Activation.h
 *
 *  Created on: Feb 3, 2019
 *      Author: ibrahim
 */

#ifndef SRC_ACTIVATION_H_
#define SRC_ACTIVATION_H_

#include <string.h>
#include <stdio.h>
#include <math.h>

class Activation {
private:
	char *act_str;
public:
	typedef enum {
		 RELU, LINEAR, RAMP
	} ACTIVATION;

	Activation();
	Activation(char *s);
	ACTIVATION get_activation();
	void activate_array(float *x, int n, Activation::ACTIVATION a);
};

#endif /* SRC_ACTIVATION_H_ */
