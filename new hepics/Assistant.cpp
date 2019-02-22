/*
 * Assistant.cpp
 *
 *  Created on: Feb 4, 2019
 *      Author: mehyar
 */

#include "Assistant.h"
namespace hepics {

Assistant::Assistant(std::string path) {
	//: net {8,"AlexNet"}
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

std::vector<unique_ptr<Image>> &Assistant::getInputs() {
	return inputs;
}


/*const Network Assistant::getNetwork() const {
	return net;
}

void Assistant::setNet(Network net) {
	this->net = net;
}*/

//loads the classnames file into a list
void Assistant::loadClassNames() {
	try {
		std::ifstream f(this->classNamesPath);

		if (!f) {
			std::cerr << "ERROR: Cannot open 'classnames.txt'!" << std::endl;
			exit(1);
		}
		std::string line;

		while (std::getline(f, line)) {
			this->classnames.push_back(line);
			//std::cout << this->classnames.back() << std::endl;
		}
	} catch (const std::exception& ex) {
		std::cerr << "Exception: '" << ex.what() << "'!" << std::endl;
		exit(1);
	}
}

//matches the add button
void Assistant::addInputImage(string path) {
	//Image input= Image::load_image(path, 0,0,3);
	auto input = make_unique<Image>(227, 227, 3);
	input->load_image(path);
	//not willing to resize, values of length and width are to be set afterwards
	this->inputs.push_back(move(input));
}

//matches the delete button
Ptr Assistant::deleteImage(Image input) {
	auto it =find_if(inputs.begin(), inputs.end(), [&](Ptr& obj){return obj->id== input.id;});
	if(it!= inputs.end()){
		auto retval = std::move(*it);
		inputs.erase(it);
		return std::move(retval);
	}
	return{};
}

	/*for (auto it = inputs.begin(); it != inputs.end(); ++it) {
		if((*it)->id==input.id){
			this->inputs.erase(it);
			break;
		}
	}*/


std::vector<string> Assistant::getClassnames() {
	return classnames;
}

//matches the reset button
void Assistant::resetInputs() {
	this->inputs.clear();
}
} // namespace hepics

