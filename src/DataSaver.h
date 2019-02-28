#pragma once

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
	std::map<int,unique_ptr<Result>> resultMap;
	vector<unique_ptr<Image>> outputs;
public:
	DataSaver();
	virtual ~DataSaver();
	void add_result(int id, unique_ptr<Result> result);
	void delete_result(int id);
	void set_result(int id, unique_ptr<Result> result);
	unique_ptr<Result> &get_result(int id);

	void add_output(unique_ptr<Image>&& output);
	vector<unique_ptr<Image>> &getOutputs();

	void write_result_in_file(int id);

	Result aggregate();

	std::vector<pair<std::string, float> > convertToVector(std::map<std::string,float> map);
};
} // namespace hepics
