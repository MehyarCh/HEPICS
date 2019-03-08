/*
 * Classifier.cpp
 *
 *  Created on: Feb 20, 2019
 *      Author: mehyar
 */

#include "Classifier.h"
#include <iostream>
namespace hepics {
using namespace std;
Classifier::Classifier(Scheduler& scheduler, DataSaver& datasaver, Network& network, Assistant& assistant) :
		scheduler { scheduler }, datasaver { datasaver }, network { network }, assistant { assistant }, is_running {
				false }, canceled { false } {
}

Classifier::~Classifier() {
	// TODO Auto-generated destructor stub
}

void Classifier::start() {
	is_running = true;
	unique_ptr<Image> output = NULL;
	while (!canceled) {
		for (auto const& input : assistant.get_input_map()) {
			output = std::make_unique<Image>(*(input.second));
			for (auto const& l : network.get_layers()) {
				if (scheduler.getUsedPlatforms()[3] && l->get_type() == Layer::Type::convolutional) {
					//run on fpga
				} else {
					output = l->forward_layer(*output);
				}
				cout << "output->width = " << output->width << ", output->height = " << output->height
						<< ", output->channels = " << output->channels << ", output->num = "
						<< output->num << "\n";
			}
			//datasaver.add_result(output->id,  r));
			datasaver.process_output(move(output), input.second->id);
		}
		return;
	}
}
void Classifier::pause() {
	is_running = false;
}
void Classifier::resume() {
	is_running = true;
}
void Classifier::cancel() {
	is_running = false;
	canceled = true;
}
}
