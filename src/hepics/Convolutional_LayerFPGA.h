#pragma once

#include "Image.h"
#include "Layer.h"

namespace hepics {

class Convolutional_LayerFPGA: public Layer {
public:
	Convolutional_LayerFPGA();
	unique_ptr<Image> forward_layer(const Image &input) override;
	Type get_type() override;
};

} // namespace hepics
