/*
 * Network.cpp
 *
 *  Created on: Feb 20, 2019
 *      Author: mehyar
 */

#include "Network.h"
namespace hepics{
Network::Network(int number_of_layers, string name) {
	this->number_of_layers = number_of_layers;
	this->name=name;
}

Network::~Network() {
	// TODO Auto-generated destructor stub
}

std::vector<unique_ptr<Layer>> &Network::get_layers(){
	return layers;
}
}
