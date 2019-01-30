/*
 * DataSaver.cpp
 *
 *  Created on: Jan 15, 2019
 *      Author: Mehyar
 */

#include "DataSaver.h"
#include "Image.h"
#include <map>
#include "Result.h"
#include <fstream>
#include <string>
#include <iostream>
#include <list>

using namespace std;

DataSaver::DataSaver() {
		// TODO Auto-generated constructor stub
}

DataSaver::~DataSaver() {
	// TODO Auto-generated destructor stub
}
void DataSaver::addResult(Image input, Result result){
	resultMap.insert(std::pair<int,Result>(input.getId(),result));
}
void DataSaver::setResult(Image input, Result result){
	resultMap.insert(std::pair<int,Result>(input.getId(),result));
}
Result DataSaver::getResult(Image input){
	return resultMap[input.getId()];
}
void DataSaver::writeResultInFile(Image input){
	std::ofstream out("ClassificationResults.txt");
	out << resultMap[input.getId()].toString();
}

void aggregate(list<Image> images){
	//1- each image has 4 class names, add these to one map (globalMap) on this class, total of 4* number of images class names
	//2- if class name already exists in globalMap, add percentage of current image classification
	//3- parse through whole globalMap and select 4 biggest percentages
	//4- divide percentages by 4 and save aggregation as a new Result

	map<string,float> global;
	std::list<Image>::iterator it;
	for (it = images.begin() ; it != images.end(); ++it){
	}


}
