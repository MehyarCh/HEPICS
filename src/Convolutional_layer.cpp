#include "Convolutional_layer.h"

namespace hepics {

using namespace std;

// TODO add padding
Convolutional_layer::Convolutional_layer(const Image &filter, size_t filter_stride, size_t pad) :
		filter { filter }, filter_stride { filter_stride }, pad { pad } {
}

unique_ptr<Image> Convolutional_layer::forward_layer(const Image &input) {
	float sum = 0;

	auto out_width = (input.width - filter.width) / filter_stride + 1;
	auto out_height = (input.height - filter.height) / filter_stride + 1;
	auto out_channels = input.channels;
	auto out_num = input.num;

	auto result = make_unique < Image > (out_width, out_height, out_channels, out_num);

	size_t filter_size = filter.width;
	size_t filter_offset = filter_size / 2;

	size_t curr_x;
	size_t curr_y;
	size_t curr_c;
	size_t curr_n;

	size_t yo;
	size_t xo;
	for (size_t no = 0; no < out_num; no++) {
		for (size_t co = 0; co < out_channels; co++) {
			for (yo = 0; yo < out_height; yo++) {
				for (xo = 0; xo < out_width; xo++) {
					// Go through filter
					for (size_t yf = 0; yf < filter_size; ++yf) {
						for (size_t xf = 0; xf < filter_size; ++xf) {
							curr_x = xo * filter_stride - filter_offset + xf;
							curr_y = yo * filter_stride - filter_offset + yf;
							curr_c = co;
							curr_n = no;
							// check if coordinates are within image
							if (curr_x >= 0 && curr_y >= 0 && curr_x <= input.width
									&& curr_y <= input.height)
								sum += input.at(curr_x, curr_y, curr_c, curr_n)
										* (filter.at(xf, yf, co, no));
						}
					}
					// save results after going through filter
					result->at(xo, yo, co, no) = sum;
				}
			}
		}
	}

	return result;
}

Layer::Type Convolutional_layer::get_type() {
	return Type::convolutional;
}

} //namespace hepics

