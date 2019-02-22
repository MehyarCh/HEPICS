/*
 * Classifier.h
 *
 *  Created on: Feb 20, 2019
 *      Author: mehyar
 */

#pragma once
namespace hepics{
class Classifier {
private:
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

