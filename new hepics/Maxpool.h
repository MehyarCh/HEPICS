#pragma once

#include "Layer.h"

namespace hepics {


class Maxpool : public Layer {
public:
	Maxpool();
	virtual ~Maxpool();
	unique_ptr<Image> forward_layer(const Image &input) override;
};

} // namespace hepics
