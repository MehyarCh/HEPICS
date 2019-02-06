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
#include "NeuralNetwork.h"
#include "DataSaver.h"
#include "ImageManager.h"
using namespace std;

class Assistant {
private:
	std::list<Image> inputs;
	std::string classNamesPath;
	NeuralNetwork net;
	ImageManager manager;
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
	const ImageManager getManager() const;
	void setManager(ImageManager manager);
	const NeuralNetwork getNetwork() const;
	void setNet(NeuralNetwork network);
	void loadClassNames();
	void addInputImage(char *path);
	void deleteImage(Image input);
	void resetInputs();

};

#endif /* ASSISTANT_H_ */
