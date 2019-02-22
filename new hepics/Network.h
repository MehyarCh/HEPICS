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

namespace hepics{
using std::string;
using PtrL=unique_ptr<Layer>;

class Network {
private:
	int number_of_layers;
	string name;
	vector<PtrL> layers;

public:
	Network(int number_of_layers, string name);

	virtual ~Network();
};
} //namespace hepics

