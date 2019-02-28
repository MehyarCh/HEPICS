#pragma once

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
	void add_result(Image input, Result result);
	void set_result(Image input, Result result);
	void delete_result(Image input);
	Result getResult(Image input);

	void add_output(unique_ptr<Image>&& output);
	vector<unique_ptr<Image>> &getOutputs();

	void writeResultInFile(Image input);

	Result aggregate(vector<Image> images);

	std::vector<pair<std::string, float> > convertToVector(std::map<std::string,float> map);
};
} // namespace hepics
