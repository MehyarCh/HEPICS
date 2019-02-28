#include "Classifier.h"
#include "Scheduler.h"
#include "Parser.h"
#include <memory>
#include <iostream>

using namespace hepics;
using std::unique_ptr;
Network network;
Assistant assistant;
Scheduler scheduler;
DataSaver datasaver;
Classifier classifier;



//unique_ptr<Network> network;
Parser parser;
int main(int argc, char **argv) {
	string path="./Pictures/dog.jpg";
	classifier = Classifier( scheduler,  datasaver, network, assistant);
	//network = parser.parse_network();
	scheduler.choosePlatforms(true,false,false);
	scheduler.chooseMode(high_performance);
	assistant.add_input_map(path);
	classifier.start();
	Result result=datasaver.get_result(assistant.get_input_map()[path]->id);
	result.display_result();

	return 0;
}
