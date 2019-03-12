/*
 * Classifier.cpp
 *
 *  Created on: Feb 20, 2019
 *      Author: mehyar
 */

#include "Classifier.h"
#include <iostream>
#include <chrono>
namespace hepics {
using namespace std;
Classifier::Classifier(Scheduler& scheduler, DataSaver& datasaver, Network& network, Assistant& assistant) :
		scheduler { scheduler }, datasaver { datasaver }, network { network }, assistant { assistant }, running { false },
				paused { false }, canceled { false }, input_count { 0 } {
}

Classifier::~Classifier() {
	cancel();
	if (worker.joinable()) {
		worker.join();
	}
}

bool Classifier::start() {
	if (running) {
		return false;
	}
	running = true;
	paused = false;
	canceled = false;

	datasaver.clear();

	auto input_vec = vector<unique_ptr<Image>> { };
	for (auto const& input : assistant.get_input_map()) {
		input_vec.push_back(make_unique<Image>(*input.second));
	}

	input_count = input_vec.size() * network.get_layers().size();
	processed = 0;

	if (worker.joinable()) {
		worker.join();
	}
	worker = thread([this](vector<unique_ptr<Image>> input_vec, bool use_fpga) {
		struct On_exit {
			atomic_bool &running;
			~On_exit() {
				running = false;
			}
		};
		auto output_vec = vector<pair<unique_ptr<Image>, int>> {};
		auto on_exit = On_exit {running};
		for (auto &input : input_vec) {
			auto id = input->id;
			auto output = move(input);
			for (auto &layer : network.get_layers()) {
				if (canceled) {
					return;
				}
				while (paused) {
					this_thread::sleep_for(1s);
				}
				if (use_fpga && layer->get_type() == Layer::Type::convolutional) {
				} else {
					output = layer->forward_layer(*output);
				}
				++processed;
			}
			output_vec.push_back(pair<unique_ptr<Image>, int>(move(output), id));
		}
		set_output_vec(move(output_vec));
	}, move(input_vec), scheduler.getUsedPlatforms()[3]);
	return true;
}
void Classifier::pause() {
	paused = true;
}
void Classifier::resume() {
	paused = false;
}
void Classifier::cancel() {
	paused = false;
	canceled = true;
}

bool Classifier::is_running() const {
	return running;
}

bool Classifier::is_canceled() const {
	return canceled;
}

void Classifier::save_results() {
	auto output_vec = move_output_vec();
	for (auto &output : output_vec) {
		datasaver.process_output(move(output.first), output.second);
	}
}

float Classifier::get_progress() const {
	return float(processed) / float(input_count);
}

void Classifier::set_output_vec(vector<pair<unique_ptr<Image>, int>> output_vec) {
	lock_guard<mutex> lock(output_vec_mutex);
	this->output_vec = move(output_vec);
}

vector<pair<unique_ptr<Image>, int>> Classifier::move_output_vec() {
	lock_guard<mutex> lock(output_vec_mutex);
	return move(output_vec);
}

}
