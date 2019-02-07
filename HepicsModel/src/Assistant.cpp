/*
 * Assistant.cpp
 *
 *  Created on: Feb 4, 2019
 *      Author: mehyar
 */

#include "Assistant.h"

Assistant::Assistant(std::string path) {
	this->classNamesPath = path;
}

Assistant::~Assistant() {
	// TODO Auto-generated destructor stub
}

const std::string Assistant::getClassNamesPath() const {
	return classNamesPath;
}

void Assistant::setClassNamesPath(std::string classNamesPath) {
	this->classNamesPath = classNamesPath;
}

const DataSaver Assistant::getDataBase() const {
	return dataBase;
}

void Assistant::setDataBase(DataSaver dataBase) {
	this->dataBase = dataBase;
}

const std::list<Image> Assistant::getInputs() const {
	return inputs;
}

void Assistant::setInputs(std::list<Image> inputs) {
	this->inputs = inputs;
}


const NeuralNetwork Assistant::getNetwork() const {
	return net;
}

void Assistant::setNet(NeuralNetwork net) {
	this->net = net;
}

//loads the classnames file into a list
void Assistant::loadClassNames(){
	std::string line;
    std::list<std::string> classes;

    std::ifstream f(this->classNamesPath);
    while (std::getline(f,line)){
        classes.push_back(line);
    }
}

//matches the add button
void Assistant::addInputImage(char *path){
	Image input= Image::load_image(path, 800,800,3);
	this->inputs.push_back(input);
}

//matches the delete button
void Assistant::deleteImage(Image input){
	bool deleted= false;
	std::list<Image>::iterator it= this->inputs.begin();
	while(!deleted && it!= inputs.end()){
		if(it->getId()==input.getId()){
			this->inputs.erase(it);
			deleted=true;
		}else{
			it++;
		}
	}
}

//matches the reset button
void Assistant::resetInputs(){
	this->inputs.clear();
}



