#pragma once

#include <vector>
#include <memory>
#include "Image.h"
#include "Layer.h"
#include "Exception.h"

namespace hepics {

using std::unique_ptr;
using std::vector;

class Convolutional_layer : public Layer {
public:
	Convolutional_layer(unique_ptr<Image> filters, vector<float> bias, size_t stride, size_t pad, size_t groups, size_t index);
	unique_ptr<Image> forward_layer(const Image &input) override;
	unique_ptr<Image> forward_layer_fpga(const Image &input);
	Type get_type() override;

private:
	unique_ptr<Image> filters;
	vector<float> bias;
	size_t stride;
	size_t pad;
	size_t groups;
	size_t index;
};

class Invalid_convolution_param: public Exception {
public:
	const char *what() const noexcept override;
};

} // namespace hepics

