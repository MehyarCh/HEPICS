/*]\
 * '''''''''''''''''''''''''''''''
 * Local_response_normalization_layer.cpp
 *
 *  Created on: Feb 27, 2019
 *      Author: Linjuan
 */
#include "Local_response_normalization_layer.h"

namespace hepics {

using namespace std;

Local_response_normalization_layer::Local_response_normalization_layer() {

}

unique_ptr<Image> Local_response_normalization_layer::forward_layer(const Image &input) {
	auto output_width = input.width;
	auto output_height = input.height;
	auto output_channels = input.channels;

	auto output = make_unique<Image>(output_width, output_height, output_channels);

    int local_size = 5;
    float alpha = 0.0001;
    float beta = 0.75;

	for (int y = 0; y < output_height; y++) {
		for (int x = 0; x < output_width; x++) {
			for (int c = 0; c < output_channels; c++) {
				float product = 0;
				int from = (c - local_size > 0) ? c - local_size : 0;
				int to = (output_channels - 1 > c + local_size) ? c + local_size : output_channels - 1;

				for (int i = from; i <= to; i++) {
					product += (input.at(x, y, i)) ^ 2;
				}

			    output->at(x, y, c) = (output->at(x, y, c) / (alpha * product) ^ beta);
			}
		}
	}
	return output;
}

} // namespace hepics



