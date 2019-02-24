#pragma once

#include "Worker.h"
#include "Convolutional_layer.h"
#include "Maxpool_layer.h"
#include "Fully_connected_layer.h"

namespace hepics {

class Worker_cpu: public Worker {
public:
	Worker_cpu();
	void assign_layer(Layer* layer) override;
	void run() override;
private:
	Layer* curr;
};

} // namespace hepics
