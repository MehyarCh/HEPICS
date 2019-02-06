/*
 * Softmax_layer.cpp
 *
 *  Created on: Jan 28, 2019
 *      Author: ibrahim
 */

#include "Softmax_layer.h"

Softmax_layer::Softmax_layer() {

}

Softmax_layer::Softmax_layer(int inputs) {
    fprintf(stderr, "softmax                                        %4d\n",  inputs);
    this->type = Layer_Type::SOFTMAX;
    this->inputs = inputs;
    this->outputs = inputs;
    this->output = (float *)calloc(inputs, sizeof(float));
    this->cost = (float *)calloc(1, sizeof(float));


}

void Softmax_layer::forward_layer(Network *net) {
	return;
}
