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
	is_running = true;
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
