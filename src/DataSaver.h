/*
 * DataSaver.h
 *
 *  Created on: Jan 15, 2019
 *      Author: Mehyar
 */

#ifndef DATASAVER_H_
#define DATASAVER_H_

#include <list>
#include <map>

#include "Image.h"
#include "Result.h"
#include <algorithm>
#include <fstream>
#include <memory>



namespace hepics{
using std::vector;
using std::map;
using std::unique_ptr;

class DataSaver {
private:
	std::map<int,Result> resultMap;
	std::vector<unique_ptr<Image>> outputs;
public:
	DataSaver();
	virtual ~DataSaver();
	void addResult(Image input, Result result);
	void setResult(Image input, Result result);
	void deleteResult(Image input);
	Result getResult(Image input);

	void add_output(unique_ptr<Image>&& output);
	vector<unique_ptr<Image>> &getOutputs();

	void writeResultInFile(Image input);

	Result aggregate(list<Image> images);

	std::vector<pair<std::string, float> > convertToVector(std::map<std::string,float> map);
};
} // namespace hepics
#endif /* DATASAVER_H_ */
