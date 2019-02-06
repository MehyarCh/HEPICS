/*
 * Scheduler.cpp
 *
 *  Created on: Feb 6, 2019
 *      Author: mehyar
 */

#include "Scheduler.h"

Scheduler::Scheduler() {
	this->mode= standard;
}
Scheduler::~Scheduler() {
	// TODO Auto-generated destructor stub
}

bool Scheduler::cpuActive() const {
	return activate_cpu;
}

void Scheduler::setCpu(bool activate){
	activate_cpu = activate;
}

bool Scheduler::fpgaActive() const{
	return activate_fpga;
}

void Scheduler::setFpga(bool activate) {
	activate_fpga = activate;
}

bool Scheduler::gpuActive() const {
	return activate_gpu;
}

void Scheduler::setGpu(bool activate) {
	activate_gpu = activate;
}


