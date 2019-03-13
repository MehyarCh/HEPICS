/*
 * Assistant.h
 *
 *  Created on: Feb 4, 2019
 *      Author: mehyar
 */

#pragma once


#include "Image.h"
#include <fstream>
#include <exception>
#include <errno.h>
#include <memory>
#include <iostream>
#include <algorithm>


namespace hepics {
using std::cout;

using std::endl;
using std::unique_ptr;
using std::string;
using std::map;

class Assistant {
private:
	map<string,unique_ptr<Image>> input_map;
	vector<float> mean_vector;

public:
	Assistant();
	Assistant(std::string path);
	virtual ~Assistant();

	void add_input_map(string path);
	void delete_input_map(string path);
	void reset_input_map();
	Image *get_input_image(const string &path);
	const map<string,unique_ptr<Image>> &get_input_map() const;

	std::vector<string> getClassnames();
};
} // namespace hepics

