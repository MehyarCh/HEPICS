#include "Maxpool.h"
#include <iostream>

namespace hepics {

using namespace std;
Maxpool::Maxpool() {
	// TODO Auto-generated constructor stub

}

unique_ptr<Image> Maxpool::forward_layer(const Image &input) {

	int filter_size = 3;
	int filter_stride = 2;
	int filter_padding = 0;
	float max = 0;

	auto x_size = (input.width - filter_size) / filter_stride + 1;
	auto y_size = (input.height - filter_size) / filter_stride + 1;
	auto z_size = input.channels;
	float t = 0;

	auto res = make_unique<Image>(x_size, y_size, z_size);

	for (int c = 0; c < res->channels; c++) {
		for (int y = 0; y < res->height; y++) {
			for (int x = 0; x < res->width; x++) {
				for (int j = 0; j < filter_size; ++j) {
					for (int i = 0; i < filter_size; ++i) {
						if (((x * filter_stride + i) < (input.width))
								&& ((y * filter_stride + j) < (input.height))) {
							t = input.at(x * filter_stride + i,
									y * filter_stride + j, c);
							max = (t > max) ? t : max; // check it later
						}
					}
				}

				res->at(x, y, c) = max;
			}
		}
	}
	return res;

}

} // namespace hepics
