/*
 * Classifier.h
 *
 *  Created on: Feb 3, 2019
 *      Author: ibrahim
 */

#ifndef SRC_CLASSIFIER_H_
#define SRC_CLASSIFIER_H_

#include <stdio.h>
#include <time.h>
#include "Image.h"
#include "Utils.h"
#include "Parser.h"
#include "Options_list.h"

#define TOP 5

class Classifier {
private:
	bool is_running=false;
	bool canceled=false;
public:
	Classifier();

	void run_classifier(int argc, char **argv);
	void predict_classifier(char *datacfg, char *cfgfile, char *weightfile, char *filename, int top);
	void pause();
	void resume();
	void cancel();
};

#endif /* SRC_CLASSIFIER_H_ */
