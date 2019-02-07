/*
 * Classifier.cpp
 *
 *  Created on: Feb 6, 2019
 *      Author: mehyar
 */

#include "Classifier.h"

Classifier::Classifier() {
	// TODO Auto-generated constructor stub

}

Classifier::~Classifier() {
	// TODO Auto-generated destructor stub
}

bool Classifier::getIsRunning() const {
	return is_running;
}

void Classifier::setIsRunning(bool isRunning) {
	is_running = isRunning;
}

void Classifier::run(){
	setIsRunning(true);
	while(getIsRunning()){

	}
}
void Classifier::pause(){
	setIsRunning(false);
}
void Classifier::resume(){
	setIsRunning(true);
}

