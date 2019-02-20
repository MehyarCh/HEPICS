/*
 * AssistantTest.cpp
 *
 *  Created on: Feb 14, 2019
 *      Author: mehyar
 */
#include "Assistant.h"
#include <gtest/gtest.h>
#include <list>
#include <iostream>
using namespace std;
Assistant *assist= new Assistant("/home/mehyar/localRepository/hepics/HepicsModel/test/Classname/classnames.txt");
Image dog = Image::load_image((char *)"/home/mehyar/localRepository/hepics/HepicsModel/test/Pictures/dog.jpeg", 275, 183,3);


void test_add_input(){
	char s[] = "/home/mehyar/localRepository/hepics/HepicsModel/test/Pictures/dog.jpeg";
	assist->addInputImage(s);
	//w= 275, h=183
}
void test_add_input2(){
	assist->addInputImage((char *)"/home/mehyar/localRepository/hepics/HepicsModel/test/Pictures/dog.jpeg");
	//w=282 , h=179
}

void test_delete_input(){
	//assert(assist->getInputs().size()==2);
	assist->deleteImage(dog);
}

void test_reset_input(){
	assist->resetInputs();
}

void test_load_classnames(){
	assist->loadClassNames();
	/*int size= assist->getClassnames().size();
	cout << size << "= size 1";*/
}

TEST(add_input, add_one_image){
	test_add_input();
	ASSERT_EQ(assist->getInputs().size(), 1);
}
TEST(add_input2, add_two_images){
	test_add_input2();
	ASSERT_EQ(assist->getInputs().size(), 2);
}
TEST(delete_input, delete_second_image){
	test_delete_input();
	ASSERT_EQ(assist->getInputs().size(), 1);
}


TEST(reset_input, clear_image){
	test_reset_input();
	ASSERT_EQ(assist->getInputs().size(), 0);
}

TEST(load_classnames, load_classnames){
	test_load_classnames();
	std::list<string>::iterator it;
	if (assist->getClassnames().empty()){
		std::cout << "empty";
		FAIL();
	}
	it = assist->getClassnames().begin();
	ASSERT_EQ(*it,"dog");
}

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






