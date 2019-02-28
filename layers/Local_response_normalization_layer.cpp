/*]\
 * '''''''''''''''''''''''''''''''
 * Local_response_normalization_layer.cpp
 *
 *  Created on: Feb 27, 2019
 *      Author: Linjuan
 */
#include "Local_response_normalization_layer.h"
#include <cmath>
#include <iostream>

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

	for (int y = 0; y < output->height; y++) {
		for (int x = 0; x < output->width; x++) {
			for (int c = 0; c < output->channels; c++) {
				float product = 0;
				int from = fmax (c - local_size, 0);
				int to = fmin (input.channels - 1, c + local_size);
				for (int i = from; i <= to; i++) {
					float value = input.at(x, y, i);
					product += value * value;
				}
			    output->at(x, y, c) = input.at(x, y, c) / pow(alpha * product, beta);
			}
		}
	}
	return output;
}

} // namespace hepics



