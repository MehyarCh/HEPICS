/*
 * SchedulerTest.cpp
 *
 *  Created on: Feb 10, 2019
 *      Author: mehyar
 */
#include <gtest/gtest.h>
#include "hepics/Scheduler.h"
//#include <assert.h>
#include <vector>

using namespace hepics;

//TEST(id,1){}

bool activated;
Scheduler *sched= new Scheduler();

Platform p1= cpu;
Platform p2= gpu;
Platform p3= fpga;

void test_activate(Platform p){
	sched->activate(p);
}

void test_deactivate(Platform p){
	sched->deactivate(p);
}

void test_activate_deactivate(Platform p){
	sched->activate(p);
	sched->deactivate(p);
}
void test_choose_platform(){
	vector<bool> all {true,true,true};
	vector<bool> cpu_fpga {true, false, true};
	vector<bool> fpga {false, false, true};
	vector<bool> cpu {true, false, false};
	sched->choosePlatforms(all[0], all[1], all[2]);
}
void test_choose_mode(Mode test_mode){
	sched->chooseMode(test_mode);
}

//test activate();
TEST(activated, test_activate){
	test_activate(p1);
	ASSERT_EQ(sched->getPlatforms()[0],true);
}

//test deactivate()
TEST(deactivated, test_deactivate){
	test_deactivate(p1);
	ASSERT_EQ(sched->getPlatforms()[0],false);
}

//test activate then deactivate
TEST(actDeac, whenActDe){
	test_activate_deactivate(p1);
	//assert(sched->getPlatforms()[0]=true);
	ASSERT_EQ(sched->getPlatforms()[0],false);
}

//test choose platform
TEST(choose_platform, platform_choice){
	test_choose_platform();
	ASSERT_EQ(sched->getPlatforms()[0],true);
	ASSERT_EQ(sched->getPlatforms()[1],true);
	ASSERT_EQ(sched->getPlatforms()[2],true);
}

//test choose mode
TEST(choose_mode, high_performance){
	Mode mode1= high_performance;
	Mode mode2= low_power;
	Mode mode3= energy_efficient;
	test_choose_mode(mode1);
	ASSERT_EQ(sched->getMode(), mode1);
	ASSERT_EQ(sched->getUsedPlatforms()[0], true);
	ASSERT_EQ(sched->getUsedPlatforms()[1], true);
	ASSERT_EQ(sched->getUsedPlatforms()[2], true);
}



