/*
 * Parser.h
 *
 *  Created on: Feb 20, 2019
 *      Author: mehyar
 */

#pragma once

#include "Network.h"
#include "Layer.h"

namespace hepics{
using std::unique_ptr;
class Parser {
public:
	Parser();
	virtual ~Parser();
	Network& parse_network();
	unique_ptr<Layer> parse_next_layer();
};
}//namespace hepics

