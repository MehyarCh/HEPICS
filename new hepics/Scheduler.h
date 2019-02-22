/*
 * Scheduler.h
 *
 *  Created on: Feb 6, 2019
 *      Author: mehyar
 */
#pragma once
#include <vector>
#include "Worker.h"
#include "Classifier.h"

namespace hepics{
using std::vector;

enum Mode	{standard, high_performance, low_power, energy_efficient};
enum Platform	{cpu, gpu, fpga};

class Scheduler {
private:
	Classifier classifier;
	Mode mode; //which mode the user chose
	vector<bool> platforms {false,false,false};// which platforms the user enabled
	vector<bool> use_platforms {false,false,false}; //which platforms the classification is using
	vector<Worker> workers;
	bool waiting= true; //waiting for request for next worker

public:
	Scheduler(int numberOfUnits);
	virtual ~Scheduler();
	vector<bool> getPlatforms();
	vector<bool> getUsedPlatforms();
	Mode getMode();
	void setMode(Mode mode);
	void activate(Platform p);
	void deactivate(Platform p);
	void choosePlatforms(bool enable_cpu, bool enable_gpu, bool enable_fpga);
	void chooseMode(Mode mode);
	void usePlatforms(bool use_cpu, bool use_gpu, bool use_fpga);

	void next_cpu_workunit(Worker unit);
	void next_gpu_workunit(Worker unit);
	void next_fpga_workunit(Worker unit);

	void defineHighPerformance();
	void defineLowPower();
	void defineEnergyEfficient();

	void work(Worker worker);

	void pause();
	void resume();
	float getProgress();


	bool isWaiting();
	void setWaiting(bool wait);
	void next();
	void wait();
};

} //namespace hepics
