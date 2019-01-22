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

class Result{
private:
	int i;
	map<string, float> percentage;
	vector<string> classNames;
	Result::Result() {
		this->i=0;
	}

	Result::~Result() {
		// TODO Auto-generated destructor stub
	}
public:
	//needs test
	string toString(){
		return classNames[0]+":"+percentage[classNames[0]]+", "+classNames[1]+":"+percentage[classNames[1]]+", "+classNames[2]+":"+percentage[classNames[2]]+", "+classNames[3]+":"+percentage[classNames[3]];
	}
	void saveResult(float percentage, string className){
		this->percentage[className]=percentage;
		classNames[i]=className;
		i++;
		if(i==4){
			cout >> "results saved";
		}
	}

	//returns percentage at index in
	float getPercentageOf(string className){
		return percentage[className];
	}

	//returns index if true, -1 if false
	int hasClassNameAt(string className){
		bool check=false;
		for (int i=0; i<4; ++i){
			if(classNames[i]==className){
				return i;
			}
		}
		return -1;
	}

};

