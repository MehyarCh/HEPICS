/*
 * Scheduler.h
 *
 *  Created on: Feb 6, 2019
 *      Author: mehyar
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_
#include "Classifier.h"
#include <vector>

using namespace std;

enum Mode{standard, high_performance, low_power, energy_efficient};
enum Platform{cpu, gpu, fpga};

class Scheduler {
private:
	Classifier classifier;
	Mode mode;
	vector<bool> platforms {false,false,false};
	vector<bool> use_platforms {false,false,false};

public:
	Scheduler();
	virtual ~Scheduler();
	Mode getMode();
	void activate(Platform p);
	void deactivate(Platform p);
	void choosePlatforms(bool enable_cpu, bool enable_gpu, bool enable_fpga);
	void chooseMode(Mode mode);
	void usePlatforms(bool use_cpu, bool use_gpu, bool use_fpga);
	//check
	void next_cpu_workunit();
	void next_gpu_workunit();
	void next_fpga_workunit();

	void defineHighPerformance();
	void defineLowPower();
	void defineEnergyEfficient();

	//check
	void pause();
	void resume();
	float getProgress();
};

#endif /* SCHEDULER_H_ */
