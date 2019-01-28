/*
 * Result.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: Mehyar
 */
// represents the results of a classified image

#include "Result.h"
#include <string>
#include <vector>
#include <iostream>
#include <map>
using namespace std;

Result::Result() {
	this->i=0;
}

Result::~Result() {
	// TODO Auto-generated destructor stub
}
//needs test
string Result::toString(){
	return classNames[0]+":"+ to_string(percentage[classNames[0]])
			+", "+classNames[1]+":"+to_string(percentage[classNames[1]])
			+", "+classNames[2]+":"+to_string(percentage[classNames[2]])
			+", "+classNames[3]+":"+to_string(percentage[classNames[3]]);
}

void Result::saveResult(float percentage, string className){
	this->percentage[className]=percentage;
	classNames[i]=className;
	i++;
	if(i==4){
		cout << "results saved";
	}
}

//returns percentage at index in
float Result::getPercentageOf(string className){
	return percentage[className];
}

//returns index if true, -1 if false
int Result::getClassNameAt(string className){
	for (int i=0; i<4; ++i){
		if(classNames[i]==className){
			return i;
		}
	}
	return -1;
}

