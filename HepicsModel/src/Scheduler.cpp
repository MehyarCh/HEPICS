/*
 * Scheduler.cpp
 *
 *  Created on: Feb 6, 2019
 *      Author: mehyar
 */

#include "Scheduler.h"

Scheduler::Scheduler() {
	this->mode= standard;
}
Scheduler::~Scheduler() {
	// TODO Auto-generated destructor stub
}

void Scheduler::activate(Platform p){
	switch(p){
		case cpu: platforms[0]=true;
		break;
		case gpu: platforms[1]=true;
		break;
		case fpga: platforms[2]=true;
		break;
	}
}
void Scheduler::deactivate(Platform p){
	switch(p){
		case cpu: platforms[0]=false;
		break;
		case gpu: platforms[1]=false;
		break;
		case fpga: platforms[2]=false;
		break;
	}
}
void Scheduler::choosePlatforms(bool enable_cpu, bool enable_gpu, bool enable_fpga){
	if(enable_cpu){
		activate(cpu);
	}else{
		deactivate(cpu);
	}
	if(enable_gpu){
		activate(gpu);
	}else{
		deactivate(gpu);
	}
	if(enable_fpga){
		activate(fpga);
	}else{
		deactivate(fpga);
	}
}
void Scheduler::chooseMode(Mode mode){
	this->mode=mode;
}
Mode Scheduler::getMode(){
	return this->mode;
}
void Scheduler::next_cpu_workunit(){

}
void Scheduler::next_gpu_workunit(){

}
void Scheduler::next_fpga_workunit(){

}
void Scheduler::pause(){
	classifier.pause();
}
void Scheduler::resume(){
	classifier.resume();
}
float Scheduler::getProgress(){
	return 0;
	//TODo create a progress bar
}
void Scheduler::usePlatforms(bool use_cpu, bool use_gpu, bool use_fpga){
	use_platforms[0]= use_cpu;
	use_platforms[1]= use_gpu;
	use_platforms[2]= use_fpga;
}

void Scheduler::defineHighPerformance(){
	/*if(platforms[0]&&platforms[1]&&platforms[2]){
		usePlatforms(true,true,true);
	}else if(platforms[0]&&platforms[1]&&(platforms[2]==false)){
		usePlatforms()
	}*/
	usePlatforms(platforms[0],platforms[1],platforms[2]);
}
void Scheduler::defineLowPower(){

}
void Scheduler::defineEnergyEfficient(){

}

