/*
 * DataSaver.cpp
 *
 *  Created on: Jan 15, 2019
 *      Author: Mehyar
 */

#include "DataSaver.h"
#include "Image.h"
#include<map>
#include "Result.h"
#include <fstream>
#include <string>
#include <iostream>
#include <list>

using namespace std;
class DataSaver{
private:
	map<int,Result> map;

public:
	DataSaver::DataSaver() {
			// TODO Auto-generated constructor stub

	}

	DataSaver::~DataSaver() {
		// TODO Auto-generated destructor stub
	}
	void addResult(Image input, Result result){
		map[input.getId()]= result;
	}
	void setResult(Image input, Result result){
		map[input.getId()]= result;
	}
	Result getResult(Image input){
		return map[input.getId()];
	}
	void writeResultInFile(Image input){
		std::ofstream out("ClassificationResults.txt");
		out << map[input.getId()].toString();
	}

	void aggregate(list<Image> images){
		//1- each image has 4 class names, add these to one map (globalMap) on this class, total of 4* number of images class names
		//2- if class name already exists in globalMap, add percentage of current image classification
		//3- parse through whole globalMap and select 4 biggest percentages
		//4- divide percentages by 4 and save aggregation as a new Result

		std::list<Image>::iterator it;
		for (it = images.begin() ; it != images.end(); ++it){

		}
	}
};

