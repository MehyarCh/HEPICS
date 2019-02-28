#pragma once

#include "Layer.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

namespace hepics {

class Softmax_layer: public Layer {
private:
	Image filter;
	size_t filter_size;
	size_t filter_stride;

public:
	unique_ptr<Image> forward_layer(const Image &input) override;
	Type get_type() override;
};

class Relu_layer: public Layer {
public:
	unique_ptr<Image> forward_layer(const Image &input) override;
	Type get_type() override;
};

class Sigmoid_layer: public Layer {
public:
	unique_ptr<Image> forward_layer(const Image &input) override;
	Type get_type() override;
};

class Tanh_layer: public Layer {
public:
	unique_ptr<Image> forward_layer(const Image &input) override;
	Type get_type() override;
};

class Activation {
public:
	typedef enum{
	    LOGISTIC, RELU, RELIE, LINEAR, RAMP, TANH, PLSE, LEAKY, ELU, LOGGY, STAIR, HARDTAN, LHTAN, SELU
	} ACTIVATION;

	static float activate(float x, ACTIVATION a);

	/* List of activation functions */
	static float stair_activate(float x);
	static float hardtan_activate(float x);
	static float linear_activate(float x);
	static float logistic_activate(float x);
	static float loggy_activate(float x);
	static float relu_activate(float x);
	static float elu_activate(float x);
	static float selu_activate(float x);
	static float relie_activate(float x);
	static float ramp_activate(float x);
	static float leaky_activate(float x);
	static float tanh_activate(float x);
	static float plse_activate(float x);
	static float lhtan_activate(float x);

};

} // namespace hepics

