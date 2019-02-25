#pragma once

#include "Layer.h"

namespace hepics {

class Softmax_layer: public Layer {
public:
	unique_ptr<Image> forward_layer(const Image &input) override;
	string get_type() override;
private:
	string type="softmax";
};

class Relu_layer: public Layer {
public:
	unique_ptr<Image> forward_layer(const Image &input) override;
	string get_type() override;
private:
	string type="relu";

};

class Sigmoid_layer: public Layer {
public:
	unique_ptr<Image> forward_layer(const Image &input) override;
	string get_type() override;
private:
	string type="sigmoid";
};

class Tanh_layer: public Layer {
public:
	unique_ptr<Image> forward_layer(const Image &input) override;
	string get_type() override;
private:
	string type="tanh";

};

} // namespace hepics

