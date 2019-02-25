
#pragma once
#include <vector>
#include "Worker_cpu.h"
#include "Worker_gpu.h"
#include "Worker_fpga.h"

namespace hepics{
using std::vector;
using std::unique_ptr;

enum Mode	{standard, high_performance, low_power, energy_efficient};
enum Platform	{cpu, gpu, fpga};

class Scheduler {
private:
	vector<unique_ptr<Worker>> workers;
	Mode mode; //which mode the user chose
	vector<bool> platforms {false,false,false};// which platforms the user enabled
	vector<bool> use_platforms {false,false,false}; //which platforms the classification is using
	bool waiting= true; //waiting for request for next worker

public:
	Scheduler();
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

	unique_ptr<Worker> &next_cpu_workunit();
	unique_ptr<Worker> &next_gpu_workunit();
	unique_ptr<Worker> &next_fpga_workunit();

	void defineHighPerformance();
	void defineLowPower();
	void defineEnergyEfficient();

	void work(Worker *worker);

	void pause();
	void resume();
	float getProgress();


	bool isWaiting();
	void setWaiting(bool wait);
	void next();
	void wait();
};

} //namespace hepics
