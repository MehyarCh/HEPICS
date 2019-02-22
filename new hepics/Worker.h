/*
 * Worker.h
 *
 *  Created on: Feb 20, 2019
 *      Author: mehyar
 */
#pragma once
namespace hepics{

class Worker {
public:
	Worker();
	virtual ~Worker();
	virtual void run();
};
}//namespace hepics
