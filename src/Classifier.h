
#pragma once
#include "Assistant.h"
#include "Network.h"
#include "Scheduler.h"

namespace hepics{

class Classifier {
private:
	unique_ptr<Network> network;
	unique_ptr<Scheduler> scheduler;
	unique_ptr<Assistant> assistant;

	bool is_running;
	bool canceled;
public:
	Classifier();
	virtual ~Classifier();
	void start();
	void pause();
	void resume();
	void cancel();
};
} //namespace hepics

