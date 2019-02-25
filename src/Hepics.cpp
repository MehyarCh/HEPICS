#include "Classifier.h"
#include "Scheduler.h"
#include "Parser.h"
#include <memory>
#include <iostream>

using namespace hepics;
using std::unique_ptr;
unique_ptr<Classifier> classifier;
unique_ptr<Scheduler> scheduler;
unique_ptr<Assistant> assistant;
unique_ptr<DataSaver> datasaver;
//unique_ptr<Network> network;
Parser parser;
int main(int argc, char **argv) {
	//network = parser.parse_network();
	scheduler->choosePlatforms(true,false,false);
	scheduler->chooseMode(high_performance);
	assistant->addInputImage("./files/dog.jpg");
	classifier->start();
	Result result=datasaver->getResult(*(datasaver->getOutputs()[0]));
	string sresult=result.toString();

	std::cout << sresult << std::endl;
	return 0;
}
