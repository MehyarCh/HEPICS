#pragma once

#include <map>

#include "Image.h"
#include "Result.h"
#include <algorithm>
#include <fstream>
#include <memory>
#include "Exception.h"


namespace hepics{
using std::vector;
using std::map;
using std::unique_ptr;

class DataSaver {
private:
	std::map<int,unique_ptr<Result>> resultMap;
	vector<unique_ptr<Image>> outputs;
	std::vector<string> classnames;
public:
	DataSaver();
	virtual ~DataSaver();
	void delete_result(int id);
	void set_result(int id, unique_ptr<Result> result);
	unique_ptr<Result> &get_result(int id);

	void add_output(unique_ptr<Image> output);
	vector<unique_ptr<Image>> &getOutputs();

	void process_output(unique_ptr<Image> output, int id);

	void write_result_in_file(int id);

	Result aggregate();

	std::vector<pair<std::string, float> > convertToVector(std::map<std::string,float> map);
	map<int,unique_ptr<Result>> &get_map();
};

class Size_missmatch: public Exception {
public:
	const char *what() const noexcept override;
};

} // namespace hepics
