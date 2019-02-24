#include "Worker_cpu.h"

namespace hepics {

Worker_cpu::Worker_cpu() {
	curr=NULL;
}

void Worker_cpu::assign_layer(Layer* layer){
	curr=layer;
}
void Worker_cpu::run(){

}

} // namespace hepics
