/*
 * Assistant.cpp
 *
 *  Created on: Feb 4, 2019
 *      Author: mehyar
 */

#include "Assistant.h"
namespace hepics {
Assistant::Assistant(){

}

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
void Assistant::add_input_map(string path) {
	auto input = std::make_unique<Image>(227, 227, 3, 1);
		input->load_image(path);
	this->input_map.insert(std::pair<string,unique_ptr<Image>>(path,move(input)));
}

//matches the delete button
void Assistant::delete_input_map(string path) {
	this->input_map.erase(path);
}

//matches the reset button
void Assistant::reset_input_map(){
	this->input_map.clear();
}

std::map<string,unique_ptr<Image>> &Assistant::get_input_map(){
	return this->input_map;
}


std::vector<string> Assistant::getClassnames() {
	return classnames;
}

} // namespace hepics

