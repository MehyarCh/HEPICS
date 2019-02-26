/*
 * Assistant.h
 *
 *  Created on: Feb 4, 2019
 *      Author: mehyar
 */

#pragma once


#include "Image.h"
#include <fstream>
#include <exception>
#include <errno.h>
#include <memory>
#include <iostream>
#include <algorithm>


namespace hepics {
using std::cout;

using std::endl;
using std::unique_ptr;
using std::string;
using Ptr=unique_ptr<Image>;

class Assistant {
private:
	std::vector<string> classnames;
	std::vector<unique_ptr<Image>> inputs;
	std::string classNamesPath;
	//Network net;
	//DataSaver dataBase;
public:
	Assistant();
	Assistant(std::string path);
	virtual ~Assistant();

	const std::string getClassNamesPath() const;
	void setClassNamesPath(std::string classNamesPath);

	//const DataSaver getDataBase() const;
	//void setDataBase(DataSaver dataBase);

	std::vector<unique_ptr<Image>> &getInputs();

	void loadClassNames();

	void addInputImage(string path);
	Ptr deleteImage(Image input);
	void resetInputs();

	std::vector<string> getClassnames();
};
} // namespace hepics

