
#include "Network.h"

namespace hepics{
using namespace caffemodel;
Network::Network() : layers { Model::parse_layers(Paths::path) } {
}

Network::~Network() {
	// TODO Auto-generated destructor stub
}

std::vector<unique_ptr<Layer>> &Network::get_layers(){
	return layers;
}
}
