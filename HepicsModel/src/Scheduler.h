/*
 * Scheduler.h
 *
 *  Created on: Feb 6, 2019
 *      Author: mehyar
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_
#include "Classifier.h"

class Scheduler {
private:
	enum Mode{standard, high_performance, low_power, energy_efficient};
	Classifier classifier;
	bool activate_cpu=true;
	bool activate_fpga=false;
	bool activate_gpu=false;
	Mode mode;
public:
	Scheduler();
	virtual ~Scheduler();
	bool cpuActive() const;
	void setCpu(bool activate);
	bool fpgaActive() const;
	void setFpga(bool activate);
	bool gpuActive() const;
	void setGpu(bool activate);
};

#endif /* SCHEDULER_H_ */
