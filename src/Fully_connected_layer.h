#pragma once

#include "Layer.h"

namespace hepics {

using std::unique_ptr;

class Fully_connected_layer: public Layer {
public:
	Fully_connected_layer(const Image &weights);
	unique_ptr<Image> forward_layer(const Image &input) override;

	const Image weights;

	Type get_type() override;
};

} // namespace hepics

