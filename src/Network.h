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
#include "Paths.h"

namespace hepics{
using std::string;
using PtrL=unique_ptr<Layer>;

class Network {
private:
	vector<PtrL> layers;
	//static constexpr auto path = "/home/mehyar/cfg/bvlc_alexnet.caffemodel";

public:
	Network();

	virtual ~Network();

	std::vector<unique_ptr<Layer>> &get_layers();
};
} //namespace hepics

