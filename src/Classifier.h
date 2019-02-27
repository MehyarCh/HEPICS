
#pragma once
#include "Assistant.h"
#include "Network.h"
#include "Scheduler.h"
#include "DataSaver.h"
#include "Layer.h"

namespace hepics{

class Classifier {
private:
	Scheduler& scheduler;
	DataSaver& datasaver;
	Network& network;

	Assistant& assistant;

	bool is_running;
	bool canceled;
public:
	Classifier(Scheduler& scheduler, DataSaver& datasaver, Network& network, Assistant& assistant);
	virtual ~Classifier();
	void start();
	void pause();
	void resume();
	void cancel();

};
} //namespace hepics

