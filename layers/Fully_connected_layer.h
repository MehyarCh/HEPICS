/*
 * Fully_connected_layer.h
 *
 *  Created on: Feb 25, 2019
 *      Author: Bahaa, Linjuan
 */
#pragma once

#include "Layer.h"

namespace hepics {

class Fully_connected_layer: public Layer {
public:
	Fully_connected_layer(const Image &weights);
	unique_ptr<Image> forward_layer(const Image &input) override;

	const Image weights;

};

} // namespace hepics
