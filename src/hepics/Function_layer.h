#pragma once

#include "Layer.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

namespace hepics {

class Softmax_layer: public Layer {
public:
	unique_ptr<Image> forward_layer(const Image &input) override;
	Type get_type() override;
};

class Relu_layer: public Layer {
public:
	unique_ptr<Image> forward_layer(const Image &input) override;
	Type get_type() override;
};

} // namespace hepics

