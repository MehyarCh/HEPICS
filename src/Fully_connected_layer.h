#pragma once

#include "Layer.h"

namespace hepics {

class Fully_connected_layer: public Layer {
public:
	Fully_connected_layer(const vector<float> &weights);
	unique_ptr<Image> forward_layer(const Image &input) override;

	const vector<float> weights;
	Type get_type() override;
};

} // namespace hepics

