#include "Maxpool_layer.h"
#include <climits>

namespace hepics {

using namespace std;

Maxpool_layer::Maxpool_layer() {
}

unique_ptr<Image> Maxpool_layer::forward_layer(const Image &input) {

	int filter_size = 3;
	int filter_stride = 2;

	auto x_size = (input.width - filter_size) / filter_stride + 1;
	auto y_size = (input.height - filter_size) / filter_stride + 1;
	auto z_size = input.channels;
	auto n_size = input.num;
	float t = 0;

	auto res = make_unique<Image>(x_size, y_size, z_size, n_size);

	for (int n = 0; n < res->num; n++) {
		for (int c = 0; c < res->channels; c++) {
			for (int y = 0; y < res->height; y++) {
				for (int x = 0; x < res->width; x++) {
					float max = numeric_limits<float>::lowest();
					for (int j = 0; j < filter_size; ++j) {
						for (int i = 0; i < filter_size; ++i) {
							if (((x * filter_stride + i) < (input.width))
									&& ((y * filter_stride + j) < (input.height))) {
								t = input.at(x * filter_stride + i,
										y * filter_stride + j, c, n);
								max = (t > max) ? t : max; // check it later
							}
						}
					}
					if (max == numeric_limits<float>::min()) {
						continue;
					}
					res->at(x, y, c, n) = max;
				}
			}
		}
	}
	return res;

}
Layer::Type Maxpool_layer::get_type() {
	return Type::maxpool;
}

} // namespace hepics
