/*
 * Convolutional.h
 *
 *  Created on: Feb 20, 2019
 *      Author: mehyar
 */

#pragma once

#include "Layer.h"

namespace hepics{

class Convolutional_layer : public Layer {
public:
	Convolutional_layer(const Image &filter, size_t filter_stride, size_t pad);
	unique_ptr<Image> forward_layer(const Image &input) override;
	Type get_type() override;
private:
	Image filter;
	size_t filter_stride;
	size_t pad;
};

} //namespace hepics


