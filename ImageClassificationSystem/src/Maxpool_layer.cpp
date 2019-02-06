/*
 * Maxpool_layer.cpp
 *
 *  Created on: Jan 28, 2019
 *      Author: ibrahim
 */

#include "Maxpool_layer.h"

Maxpool_layer::Maxpool_layer() {

}

Maxpool_layer::Maxpool_layer(int batch, int h, int w, int c, int size, int stride, int padding)
{
    this->type = Layer_Type::LAYER_TYPE::MAXPOOL;;
    this->h = h;
    this->w = w;
    this->c = c;
    this->pad = padding;
    this->out_w = (w + padding - size)/stride + 1;
    this->out_h = (h + padding - size)/stride + 1;
    this->out_c = c;
    this->outputs = this->out_h * this->out_w * this->out_c;
    this->inputs = h*w*c;
    this->size = size;
    this->stride = stride;
    int output_size = this->out_h * this->out_w * this->out_c * batch;
    this->indexes = (int *)calloc(output_size, sizeof(int));
    this->output =  (float *)calloc(output_size, sizeof(float));
    fprintf(stderr, "max          %d x %d / %d  %4d x%4d x%4d   ->  %4d x%4d x%4d\n", size, size, stride, w, h, c, this->out_w, this->out_h, this->out_c);

}

void Maxpool_layer::forward_layer(Network *net) {
    int b,i,j,k,m,n;
    int w_offset = -this->pad/2;
    int h_offset = -this->pad/2;

    int h = this->out_h;
    int w = this->out_w;
    int c = this->c;

        for(k = 0; k < c; ++k){
            for(i = 0; i < h; ++i){
                for(j = 0; j < w; ++j){
                    int out_index = j + w*(i + h*(k + c*b));
                    float max = -FLT_MAX;
                    int max_i = -1;
                    for(n = 0; n < this->size; ++n){
                        for(m = 0; m < this->size; ++m){
                            int cur_h = h_offset + i * this->stride + n;
                            int cur_w = w_offset + j * this->stride + m;
                            int index = cur_w + this->w * (cur_h + this->h * (k + b*this->c));
                            int valid = (cur_h >= 0 && cur_h < this->h &&
                                         cur_w >= 0 && cur_w < this->w);
                            float val = (valid != 0) ? net->input[index] : -FLT_MAX;
                            max_i = (val > max) ? index : max_i;
                            max   = (val > max) ? val   : max;
                        }
                    }
                    this->output[out_index] = max;
                    this->indexes[out_index] = max_i;
                }
            }
        }
}

