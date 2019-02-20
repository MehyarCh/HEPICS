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


const Network Assistant::getNetwork() const {
	return net;
}

void Assistant::setNet(Network net) {
	this->net = net;
}

//loads the classnames file into a list
void Assistant::loadClassNames(){
	try{
		std::ifstream f(this->classNamesPath);

		if(!f){
			std::cerr << "ERROR: Cannot open 'classnames.txt'!" << std::endl;
			exit(1);
		}
		std::string line;

		while (std::getline(f,line)){
			this->classnames.push_back(line);
			//std::cout << this->classnames.back() << std::endl;
		}
	}catch(const std::exception& ex){
		std::cerr << "Exception: '" << ex.what() << "'!" << std::endl;
		exit(1);
	}
}


//matches the add button
void Assistant::addInputImage(char *path){
	Image input= Image::load_image(path, 0,0,3);
	//not willing to resize, values of length and width are to be set afterwards
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

std::list<string> Assistant::getClassnames() {
	return classnames;
}

//matches the reset button
void Assistant::resetInputs(){
	this->inputs.clear();
}



