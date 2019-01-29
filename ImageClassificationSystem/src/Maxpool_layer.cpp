/*
 * Maxpool_layer.cpp
 *
 *  Created on: Jan 28, 2019
 *      Author: ibrahim
 */

#include "Maxpool_layer.h"
#include <float.h>

Maxpool_layer::Maxpool_layer(int h, int w, int c, int stride) {
	this->stride = stride;
	this->output = new Image((h - 1) / stride + 1, (w - 1) / stride + 1, c);
}

Maxpool_layer::~Maxpool_layer() {
	// TODO Auto-generated destructor stub
}

void Maxpool_layer::run_maxpool_layer(Image *input) {
    int i,j,k;
    for(i = 0; i < this->output->height * this->output->width *this->output->channels; ++i) this->output->data[i] = -DBL_MAX;
    for(i = 0; i < input->height; ++i){
        for(j = 0; j < input->width; ++j){
            for(k = 0; k < input->channels; ++k){
                double val = input->get_pixel(i, j, k);
                double cur = this->output->get_pixel(i / this->stride, j / this->stride, k);
                if(val > cur) this->output->set_pixel(i / this->stride, j / this->stride, k, val);
            }
        }
}
}
