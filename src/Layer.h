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
	enum class Type { convolutional, maxpool, softmax, fullyconnected, tanh, relu, sigmoid } ;
	Layer() = default;
	Layer(const Layer &layer) = delete;
	Layer(const Layer &&layer) = delete;
	const Layer &operator=(const Layer &layer) = delete;
	const Layer &operator=(const Layer &&layer) = delete;
	virtual ~Layer()=default;
	virtual unique_ptr<Image> forward_layer(const Image &input) = 0;
	virtual Type get_type()=0;
	const Image& getFilter() const;
	void setFilter(const Image& filter);
	size_t getFilterSize() const;
	void setFilterSize(size_t filterSize);
	size_t getFilterStride() const;
	void setFilterStride(size_t filterStride);
};

} // namespace hepics
