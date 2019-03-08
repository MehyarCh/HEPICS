/*
 * Network.h
 *
 *  Created on: Feb 20, 2019
 *      Author: mehyar
 */

#pragma once
#include <string>
#include <vector>
#include "Layer.h"
#include "Caffemodel.h"

namespace hepics{
using std::string;
using PtrL=unique_ptr<Layer>;

class Network {
private:
	vector<PtrL> layers;

public:
	Network();

	virtual ~Network();

	std::vector<unique_ptr<Layer>> &get_layers();
};
} //namespace hepics

