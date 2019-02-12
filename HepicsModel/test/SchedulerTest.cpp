/*
 * SchedulerTest.cpp
 *
 *  Created on: Feb 10, 2019
 *      Author: mehyar
 */
#include <gtest/gtest.h>
#include "Scheduler.h"
#include <assert.h>

//TEST(id,1){}

bool activated;
Scheduler *sched= new Scheduler(3);

void test_activate(){
	Platform p=cpu;
	sched->activate(p);
}

void test_deactivate(){
	Platform p= cpu;
	sched->deactivate(p);
}

void test_activate_deactivate(){
	Platform p= cpu;
	sched->activate(p);
	sched->deactivate(p);
}


//test_activate();
TEST(activated, whenActivate){
	test_activate();
	ASSERT_EQ(sched->getPlatforms()[0],true);
}

TEST(deactivated, whenDeactivate){
	test_deactivate();
	ASSERT_EQ(sched->getPlatforms()[0],false);
}
TEST(actDeac, whenActDe){
	test_activate_deactivate();
	ASSERT_EQ(sched->getPlatforms()[0],false);
}



