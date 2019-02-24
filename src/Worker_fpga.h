#pragma once

#include "Worker.h"
#include "Convolutional_LayerFPGA.h"

namespace hepics {

class Worker_fpga: public Worker {
public:
	Worker_fpga();
	void assign_layer(Layer* layer) override;
	void run() override;
private:
	Layer* curr = new Convolutional_LayerFPGA();

};

} // namespace hepics
