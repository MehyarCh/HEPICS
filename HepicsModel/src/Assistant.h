/*
 * Assistant.h
 *
 *  Created on: Feb 4, 2019
 *      Author: mehyar
 */

#ifndef ASSISTANT_H_
#define ASSISTANT_H_
#include <list>
#include <string>
#include "Image.h"
#include "Network.h"
#include "DataSaver.h"
#include <fstream>
#include <string>
#include <list>
#include <exception>
#include <errno.h>
#include <stdlib.h>
using namespace std;
using std::cout;
using std::endl;

using namespace std;

class Assistant {
private:
	std::list<string> classnames;
	std::list<Image> inputs;
	std::string classNamesPath;
	Network net= Network(8);
	DataSaver dataBase;
public:
	Assistant(std::string path);
	virtual ~Assistant();
	const std::string getClassNamesPath() const;
	void setClassNamesPath(std::string classNamesPath);
	const DataSaver getDataBase() const;
	void setDataBase(DataSaver dataBase);
	const std::list<Image> getInputs() const;
	void setInputs(std::list<Image> inputs);
	const Network getNetwork() const;
	void setNet(Network network);
	void loadClassNames();
	void addInputImage(char *path);
	void deleteImage(Image input);
	void resetInputs();
	std::list<string> getClassnames();
};

#endif /* ASSISTANT_H_ */
