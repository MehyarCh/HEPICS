/*
 * Local_response_normalization_layer.h
 *
 *  Created on: Feb 27, 2019
 *      Author: Linjuan
 */
#pragma once

#include "Layer.h"

namespace hepics {

class Local_response_normalization_layer : public Layer {
public:
	Local_response_normalization_layer ();
	unique_ptr<Image> forward_layer(const Image &input) override;
};

} // namespace hepics



