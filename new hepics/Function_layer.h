#pragma once

#include "Layer.h"

namespace hepics {

class Softmax_layer: public Layer {
public:
	unique_ptr<Image> forward_layer(const Image &input) override;
};

class Relu_layer: public Layer {
public:
	unique_ptr<Image> forward_layer(const Image &input) override;
};

class Sigmoid_layer: public Layer {
public:
	unique_ptr<Image> forward_layer(const Image &input) override;
};

class Tanh_layer: public Layer {
public:
	unique_ptr<Image> forward_layer(const Image &input) override;
};

} // namespace hepics

