#include "Maxpool_layer.h"

namespace hepics {

using namespace std;

Maxpool_layer::Maxpool_layer() {
	// TODO Auto-generated constructor stub

}

unique_ptr<Image> Maxpool_layer::forward_layer(const Image &input) {

	int filter_size = 3;
	int filter_stride = 2;

	auto x_size = (input.width - 1) / filter_stride + 1;
	auto y_size = (input.height - 1) / filter_stride + 1;
	auto z_size = input.channels;
	float t = 0;

	auto res = make_unique<Image>(x_size, y_size, z_size);

	for (int c = 0; c < res->channels; c++) {
		for (int y = 0; y < res->height; y++) {
			for (int x = 0; x < res->width; x++) {
				float max = 0;
				for (int j = -1; j < filter_size - 1; ++j) {
					for (int i = -1; i < filter_size - 1; ++i) {
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
Layer::Type Maxpool_layer::get_type(){
	return Type::maxpool;
}

} // namespace hepics
