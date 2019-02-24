#include "Worker_fpga.h"

namespace hepics {

Worker_fpga::Worker_fpga() {
	// TODO Auto-generated constructor stub

}

void Worker_fpga::assign_layer(Layer* layer){
	curr=layer;
}
void Worker_fpga::run(){
	//curr->forward_layer();
}

} // namespace hepics
