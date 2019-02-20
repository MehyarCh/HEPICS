#pragma once

#include "Image.h"
#include <memory>

namespace hepics {
using std::unique_ptr;

class Maxpool {
public:
	Maxpool();
	float getMax(int h, int w, int c);
	unique_ptr<Image> forward_layer(const Image &input);

	// Imlementieren:
};

} // namespace hepics
