/*
 * Classifier.h
 *
 *  Created on: Feb 6, 2019
 *      Author: mehyar
 */

#ifndef CLASSIFIER_H_
#define CLASSIFIER_H_

class Classifier {
private:
	bool is_running=false;
public:
	Classifier();
	virtual ~Classifier();
	void run();
	bool getIsRunning() const;
	void setIsRunning(bool isRunning = false);
	void resume();
	void pause();
};

#endif /* CLASSIFIER_H_ */
