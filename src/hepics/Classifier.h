
#pragma once
#include "Assistant.h"
#include "Network.h"
#include "Scheduler.h"
#include "DataSaver.h"
#include "Image.h"
#include "Layer.h"
#include <thread>
#include <atomic>
#include <memory>
#include <vector>
#include <mutex>

namespace hepics{

using std::vector;
using std::unique_ptr;
using std::thread;
using std::atomic_bool;
using std::atomic_size_t;
using std::mutex;

class Classifier {
private:
	Scheduler& scheduler;
	DataSaver& datasaver;
	Network& network;

	Assistant& assistant;

	thread worker;
	atomic_bool running;
	atomic_bool paused;
	atomic_bool canceled;

	size_t input_count;
	atomic_size_t processed;

	mutex output_vec_mutex;
	vector<pair<unique_ptr<Image>, int>> output_vec;
public:
	Classifier(Scheduler& scheduler, DataSaver& datasaver, Network& network, Assistant& assistant);
	virtual ~Classifier();
	bool start();
	void pause();
	void resume();
	void cancel();
	bool is_running() const;
	bool is_canceled() const;
	void save_results();
	float get_progress() const;

private:
	void set_output_vec(vector<pair<unique_ptr<Image>, int>> output_vec);
	vector<pair<unique_ptr<Image>, int>> move_output_vec();

};
} //namespace hepics

