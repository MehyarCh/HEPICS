#include "Convolutional_layer.h"

namespace hepics {

Convolutional_layer::Convolutional_layer(const Image &filter,
		size_t filter_size, size_t filter_stride) :
		filter { filter }, filter_size { filter_size }, filter_stride {
				filter_stride } {

}

unique_ptr<Image> Convolutional_layer::forward_layer(const Image &input) {
	float sum = 0;

	auto out_width = (input.width - filter.width) / filter_stride + 1;
	auto out_height = (input.height - filter.height) / filter_stride + 1;
	auto out_channels = input.channels;

	unique_ptr<Image> result(new Image(out_width, out_height, out_channels));

	size_t filter_offset = filter_size / 2;

	size_t curr_x;
	size_t curr_y;
	size_t curr_c;

	size_t yo;
	size_t xo;
	for (size_t co = 0; co < out_channels; co++) {
		for (yo = 0; yo < out_height; yo++) {
			for (xo = 0; xo < out_width; xo++) {
				// Go through filter
				for (size_t yf = 0; yf < filter_size; ++yf) {
					for (size_t xf = 0; xf < filter_size; ++xf) {
						curr_x = xo * filter_stride - filter_offset + xf;
						curr_y = yo * filter_stride - filter_offset + yf;
						curr_c = co;
						// check if coordinates are within image
						if (curr_x >= 0 && curr_y >= 0 && curr_x <= input.width
								&& curr_y <= input.height)
							sum += input.at(curr_x, curr_y, curr_c)
									* (filter.at(xf, yf, co));
					}
				}
				// save results after going through filter
				result->at(xo, yo, co) = sum;
			}
		}

	}

	return result;
}

Layer::Type Convolutional_layer::get_type(){
	return Type::convolutional;
}
}//namespace hepics


