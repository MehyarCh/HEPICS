#pragma once

#include "Worker.h"

namespace hepics {

class Worker_gpu: public Worker {
public:
	Worker_gpu();
	virtual ~Worker_gpu();
	void assign_layer(Layer* layer) override;
	void run() override;
};

} // namespace hepics
