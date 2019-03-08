#pragma once

#include <memory>
#include "Image.h"

namespace hepics {

using std::unique_ptr;

class Layer {
public:
	enum class Type { convolutional, maxpool, softmax, fullyconnected, tanh, relu, sigmoid, local_response_normalization } ;
	Layer() = default;
	Layer(const Layer &layer) = delete;
	Layer(const Layer &&layer) = delete;
	const Layer &operator=(const Layer &layer) = delete;
	const Layer &operator=(const Layer &&layer) = delete;
	virtual ~Layer()=default;
	virtual unique_ptr<Image> forward_layer(const Image &input) = 0;
	virtual Type get_type()=0;
};

} // namespace hepics

