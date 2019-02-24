/*
 * Worker.h
 *
 *  Created on: Feb 20, 2019
 *      Author: mehyar
 */
#pragma once
#include "Layer.h"

namespace hepics{

class Worker {
public:
	Worker() = default;
	Worker(const Worker &layer) = delete;
	Worker(const Worker &&layer) = delete;
	const Worker &operator=(const Worker &worker) = delete;
	const Worker &operator=(const Worker &&worker) = delete;
	virtual ~Worker()=default;
	virtual void run()=0;

	virtual void assign_layer(Layer* layer)=0;
};
}//namespace hepics
