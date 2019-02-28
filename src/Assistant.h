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

class Assistant {
private:
	std::map<string,unique_ptr<Image>> input_map;

public:
	Assistant();
	Assistant(std::string path);
	virtual ~Assistant();

	void add_input_map(string path);
	void delete_input_map(string path);
	void reset_input_map();

	std::map<string,unique_ptr<Image>> &get_input_map();

	std::vector<string> getClassnames();
};
} // namespace hepics

