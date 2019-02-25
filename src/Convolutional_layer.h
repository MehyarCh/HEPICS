/*
 * Convolutional.h
 *
 *  Created on: Feb 20, 2019
 *      Author: mehyar
 */

#pragma once

#include "Layer.h"

namespace hepics{

using std::unique_ptr;

class Convolutional_layer : public Layer {
public:
	Convolutional_layer();
	unique_ptr<Image> forward_layer(const Image &input) override;
	string get_type() override;
private:
	string type;
};

} //namespace hepics


