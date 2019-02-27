/*
 * AssistantTest.cpp
 *
 *  Created on: Feb 14, 2019
 *      Author: mehyar
 */
#include "Paths.h"
#include "Assistant.h"
#include <gtest/gtest.h>
#include <list>
#include <iostream>

using namespace hepics;
using namespace std;

Assistant *assist= new Assistant("/home/mehyar/localRepository/hepics/HepicsModel/test/Classname/classnames.txt");


void test_load_classnames(){
	assist->loadClassNames();
	/*int size= assist->getClassnames().size();
	cout << size << "= size 1";*/
}

void test_add_input_map(string path){
	assist->add_input_map(path);
}

void test_delete_input_map(string path){
	assist->delete_input_map(path);
}
void test_reset_map(){
	assist->reset_input_map();
}


TEST(test_add_map, add_input_map){
	assist->add_input_map(path::dog);
	assist->add_input_map(path::lion);
	ASSERT_EQ(assist->get_input_map().size(),2);
}
TEST(test_delete_from_map, delete_input_map){
	assist->delete_input_map(path::dog);
	ASSERT_EQ(assist->get_input_map().size(),1);
}
TEST(test_reset_map, reset_input_map){
	assist->reset_input_map();
	ASSERT_EQ(assist->get_input_map().size(),0);
}

/*TEST(load_classnames, load_classnames){
	test_load_classnames();
	std::list<string>::iterator it;
	if (assist->getClassnames().empty()){
		std::cout << "empty";
		FAIL();
	}
	it = assist->getClassnames().begin();
	ASSERT_EQ(*it,"dog");
}*/

/*TEST(load_classnames2, load_classnames2){
	test_load_classnames();
	std::list<string>::iterator it2=assist->getClassnames().begin();
	it2 = assist->getClassnames().begin();
	++it2;
	//std::cout << *it;
	ASSERT_EQ(*it2,"penguin");
}

TEST(load_classnames3, load_classnames3){
	test_load_classnames();
	std::list<string>::iterator it;
	if (assist->getClassnames().empty()){
		std::cout << "empty";
		FAIL();
	}
	it = assist->getClassnames().end();
	it--;
	ASSERT_EQ(*it,"pen");
}*/





