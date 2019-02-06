/*
 * Activation.cpp
 *
 *  Created on: Feb 3, 2019
 *      Author: ibrahim
 */

#include "Activation.h"

Activation::Activation() {
}

Activation::Activation(char *s) {
	this->act_str = s;
}

Activation::ACTIVATION Activation::get_activation() {
    if (strcmp(this->act_str, "relu")==0) return Activation::ACTIVATION::RELU;
    if (strcmp(this->act_str, "linear")==0) return Activation::ACTIVATION::LINEAR;
    if (strcmp(this->act_str, "ramp")==0) return Activation::ACTIVATION::RAMP;
    fprintf(stderr, "Couldn't find activation function %s, going with ReLU\n", this->act_str);
    return Activation::RELU;
}

float linear_activate(float x){return x;}
float logistic_activate(float x){return 1./(1. + exp(-x));}
float loggy_activate(float x){return 2./(1. + exp(-x)) - 1;}
float relu_activate(float x){return x*(x>0);}
float elu_activate(float x){return (x >= 0)*x + (x < 0)*(exp(x)-1);}
float selu_activate(float x){return (x >= 0)*1.0507*x + (x < 0)*1.0507*1.6732*(exp(x)-1);}
float relie_activate(float x){return (x>0) ? x : .01*x;}
float ramp_activate(float x){return x*(x>0)+.1*x;}
float leaky_activate(float x){return (x>0) ? x : .1*x;}
float tanh_activate(float x){return (exp(2*x)-1)/(exp(2*x)+1);}


float activate(float x, Activation::ACTIVATION a)
{
    switch(a){
        case Activation::ACTIVATION::LINEAR:
            return linear_activate(x);
        case Activation::ACTIVATION::RELU:
            return relu_activate(x);
        case Activation::ACTIVATION::RAMP:
            return ramp_activate(x);
    }
    return 0;
}

void Activation::activate_array(float *x, int n, Activation::ACTIVATION a)
{
    int i;
    for(i = 0; i < n; ++i){
        x[i] = activate(x[i], a);
    }
}
