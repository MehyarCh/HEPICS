/*
 * Classifier.cpp
 *
 *  Created on: Feb 20, 2019
 *      Author: mehyar
 */

#include "Classifier.h"
namespace hepics {
Classifier::Classifier() :
		is_running { false }, canceled { false } {
}

Classifier::~Classifier() {
	// TODO Auto-generated destructor stub
}
void Classifier::start() {
	vector<unique_ptr<Layer>> layers = std::move(network->get_layers());
	is_running = true;
	while(is_running){
		for (auto const& i: layers) {
			if(scheduler->getUsedPlatforms()[3] && i->get_type().compare("convolutional")==0){
				scheduler->next_fpga_workunit()->run();
			}else{
				scheduler->next_cpu_workunit()->run();
			}
		}
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
