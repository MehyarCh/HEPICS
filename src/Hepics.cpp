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
Classifier classifier( scheduler,  datasaver, network, assistant);



//unique_ptr<Network> network;
int main(int argc, char **argv) {
	//network = parser.parse_network();
	scheduler.choosePlatforms(true,false,false);
	scheduler.chooseMode(high_performance);
	constexpr auto p = "/home/andres/test_data/images/256x256x3/soccer_ball01.png";
	assistant.add_input_map(p);
	classifier.start();
	auto id = assistant.get_input_map()[p]->id;
	auto &result = *datasaver.get_result(id);
	result.display_result();

	return 0;
}
