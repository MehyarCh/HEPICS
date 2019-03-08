/*
 * Assistant.cpp
 *
 *  Created on: Feb 4, 2019
 *      Author: mehyar
 */

#include "Assistant.h"
#include "Paths.h"
#include "Caffemodel.h"

namespace hepics {

using namespace caffemodel;

static auto mean_image_to_mean_vector(const Image &mean_image) {
	auto mean_vector = vector<float>(mean_image.channels);
	auto f = 1.0 / double { mean_image.height * mean_image.width };
	for (size_t c = 0; c < mean_image.channels; ++c) {
		auto sum = 0.0;
		for (size_t y = 0; y < mean_image.height; ++y) {
			for (size_t x = 0; x < mean_image.width; ++x) {
				sum += mean_image.at(x, y, c, 0);
			}
		}
		mean_vector[c] = f * sum;
	}
	return mean_vector;
}

Assistant::Assistant() :
		mean_vector { mean_image_to_mean_vector(*Mean::parse_mean(Paths::mean_file)) } {
}

Assistant::~Assistant() {
	// TODO Auto-generated destructor stub
}

//matches the add button
void Assistant::add_input_map(string path) {
	auto input = std::make_unique<Image>(227, 227, 3, 1);
	input->load_image(path, mean_vector);
	this->input_map.insert(std::pair<string, unique_ptr<Image>>(path, move(input)));
}

//matches the delete button
void Assistant::delete_input_map(string path) {
	this->input_map.erase(path);
}

//matches the reset button
void Assistant::reset_input_map() {
	this->input_map.clear();
}

std::map<string, unique_ptr<Image>> &Assistant::get_input_map() {
	return this->input_map;
}

} // namespace hepics

