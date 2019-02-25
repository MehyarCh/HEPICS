#pragma once

#include "Layer.h"

namespace hepics {

class Convolutional_LayerFPGA: public Layer {
public:
	Convolutional_LayerFPGA();
	unique_ptr<Image> forward_layer(const Image &input) override;
	string get_type() override;
private:
	string type;
};

} // namespace hepics
