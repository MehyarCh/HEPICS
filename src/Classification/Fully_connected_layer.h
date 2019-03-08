#pragma once

#include "Layer.h"
#include "Exception.h"

namespace hepics {

using std::unique_ptr;

class Fully_connected_layer: public Layer {
public:
	Fully_connected_layer(const Image &weights, vector<float> bias);
	unique_ptr<Image> forward_layer(const Image &input) override;

	const Image weights;
	const vector<float> bias;

	Type get_type() override;
};

class Invalid_fully_connected_param: public Exception {
public:
	const char *what() const noexcept override;
};

} // namespace hepics

