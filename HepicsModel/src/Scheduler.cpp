/*
 * Scheduler.cpp
 *
 *  Created on: Feb 6, 2019
 *      Author: mehyar
 */

#include "Scheduler.h"

/*
 * Order of methods :
 * 1- choosePlatforms= enables platforms
 * 2- chooseMode= chooses which platforms to use corresponding to the mode, sets the array "use_platforms"
 * 3- provideWorker= gives the worker at the asked index
 */
Scheduler::Scheduler(int numberOfUnits) {
	this->mode= standard;
	this->workers.reserve(numberOfUnits);
}
Scheduler::~Scheduler() {
	// TODO Auto-generated destructor stub
}

vector<bool> Scheduler::getPlatforms(){
	return this->platforms;
}
vector<bool> Scheduler::getUsedPlatforms(){
	return this->use_platforms;
}

//enables a platform
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

//disables a platform
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

//enables platforms
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

//selects operation mode
void Scheduler::chooseMode(Mode mode){
	this->mode=mode;
	switch(mode){
		case high_performance:
			defineHighPerformance();
			break;
		case low_power:
			defineLowPower();
			break;
		case energy_efficient:
			defineEnergyEfficient();
			break;
		default :
			setMode(standard);
	}
}
Mode Scheduler::getMode(){
	return this->mode;
}
void Scheduler::setMode(Mode mode){
	this->mode=mode;
}

//only run if platform is available
void Scheduler::next_cpu_workunit(Worker worker){
	if(use_platforms[0]){
		worker.run_on_cpu();
	}
}
void Scheduler::next_gpu_workunit(Worker worker){
	if(use_platforms[1]){
		worker.run_on_gpu();
	}
}
void Scheduler::next_fpga_workunit(Worker worker){
	if(use_platforms[2]){
		worker.run_on_fpga();
	}
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

/*defining of which platforms consists each mode, depending on the available platforms
*expected mostly parallel computations and vector operations
*if no platform is enabled run on cpu by default (see last case)
*/
void Scheduler::defineHighPerformance(){
	//use all enabled platforms for max performance
	usePlatforms(platforms[0],platforms[1],platforms[2]);
}

void Scheduler::defineLowPower(){
	//idea is to only select one platform, the least power consumer when possible
	if(platforms[0]&&platforms[1]&&platforms[2]){
		usePlatforms(false,false,true);
	}else if(platforms[0]&&platforms[1]&&(platforms[2]==false)){
		usePlatforms(false, true, false);
	}else if(platforms[0]==true && platforms[1]==false && platforms[2]==true ){
		usePlatforms(false, false, true);
	}else if((platforms[0]==true) && (platforms[1]==false) && (platforms[2]==false)){
		usePlatforms(true, false, false);
	}else if(platforms[0]==false && platforms[1]==true && platforms[2]==true ){
		usePlatforms(false, false, true);
	}else if(platforms[0]==false && platforms[1]==true && platforms[2]==false ){
		usePlatforms(false, true, false);
	}else if(platforms[0]==false && platforms[1]==false && platforms[2]==true ){
		usePlatforms(false, false, true);
	}else if(platforms[0]==false && platforms[1]==false && platforms[2]==false ){
		usePlatforms(true, false, false);
	}
}

void Scheduler::defineEnergyEfficient(){
	//idea is to avoid using the cpu when possible, meaning sacrifice its performance for less power consumption
	if(platforms[0]&&platforms[1]&&platforms[2]){
		usePlatforms(true,false,true);
	}else if(platforms[0]&&platforms[1]&&(platforms[2]==false)){
		usePlatforms(false, true, false);
	}else if(platforms[0]==true && platforms[1]==false && platforms[2]==true ){
		usePlatforms(false, false, true);
	}else if(platforms[0]==true && platforms[1]==false && platforms[2]==false ){
		usePlatforms(true, false, false);
	}else if(platforms[0]==false && platforms[1]==true && platforms[2]==true ){
		//sacrificing gpu performance for less energy
		usePlatforms(false, false, true);
	}else if(platforms[0]==false && platforms[1]==true && platforms[2]==false ){
		usePlatforms(false, true, false);
	}else if(platforms[0]==false && platforms[1]==false && platforms[2]==true ){
		usePlatforms(false, false, true);
	}else if(platforms[0]==false && platforms[1]==false && platforms[2]==false ){
		usePlatforms(true, false, false);
	}
}

/*
 * Platforms Comparison:
 * 1- Parallel computations and vector operations:
 * 		Power Consumption : cpu>gpu>fpga
 * 		Performance : fpga>gpu>cpu
 * 		Efficiency : fpga>cpu>gpu
 * 2- Sequential computations and int based operations:
 * 		Power Consumption : gpu>cpu>fpga
 * 		Performance : cpu>gpu>fpga
 * 		Efficiency : cpu>fpga>gpu
 */

Worker Scheduler::provideWorker(int index){
	return workers[index];
}

//for purpose of parallelisation
bool Scheduler::isWaiting(){
	return this->waiting;
}
void Scheduler::setWaiting(bool wait){
	this->waiting=wait;
}
void Scheduler::next(){
	setWaiting(false);
}
void Scheduler::wait(){
	setWaiting(true);
}

//worker works on chosen platform
void Scheduler::work(Worker worker, Platform platform){
	switch(platform){
	case cpu:
		next_cpu_workunit(worker);
		break;
	case gpu:
		next_gpu_workunit(worker);
		break;
	case fpga:
		next_fpga_workunit(worker);
		break;
	}
}

