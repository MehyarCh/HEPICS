#pragma once

#include "Layer.h"

namespace hepics {


class Maxpool_layer : public Layer {
public:
	Maxpool_layer();
	virtual ~Maxpool_layer();
	unique_ptr<Image> forward_layer(const Image &input) override;
	Type get_type() override;

};

} // namespace hepics
