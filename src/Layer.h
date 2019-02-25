/*
 * Layer.h
 *
 *  Created on: Feb 20, 2019
 *      Author: mehyar
 */

#pragma once

#include "Image.h"
#include <memory>

namespace hepics {

using std::unique_ptr;

class Layer {
public:
	Layer() = default;
	Layer(const Layer &layer) = delete;
	Layer(const Layer &&layer) = delete;
	const Layer &operator=(const Layer &layer) = delete;
	const Layer &operator=(const Layer &&layer) = delete;
	virtual ~Layer()=default;
	virtual unique_ptr<Image> forward_layer(const Image &input) = 0;
	virtual string get_type();
};

} // namespace hepics

