/*
 * Hepics.cpp
 *
 *  Created on: Feb 3, 2019
 *      Author: ibrahim
 */

#include <iostream>
#include <string.h>
#include "Classifier.h"

int main(int argc, char **argv) {
	if(argc < 2) {
		fprintf(stderr, "arg is less than two strings");
	}

	if (0 == strcmp(argv[1], "classifier")) {
		Classifier *cl = new Classifier();
		cl->run_classifier(argc, argv);
	}
	else if (0 == strcmp(argv[1], "regressor")) {
		//Regressor *rg = new Regressor();
		//rg->run_regressor(argc, argv);
	}
	std::cout << "Hello World!!\n";
	return 0;
}

