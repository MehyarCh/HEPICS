#include "Paths.h"
#include "DataSaver.h"
namespace hepics {

using namespace std;

//loads the classnames file into a list
static std::vector<string> loadClassNames(const std::string &classNamesPath) {
	std::vector<string> classnames;
	try {
		std::ifstream f(classNamesPath);

		if (!f) {
			std::cerr << "ERROR: Cannot open 'classnames.txt'!" << std::endl;
			exit(1);
		}
		std::string line;

		while (std::getline(f, line)) {
			classnames.push_back(line);
			//std::cout << this->classnames.back() << std::endl;
		}
	} catch (const std::exception& ex) {
		std::cerr << "Exception: '" << ex.what() << "'!" << std::endl;
		exit(1);
	}
	return classnames;
}

DataSaver::DataSaver() :
		result_count{0}, classnames { loadClassNames(Paths::class_name_file) }  {
}

DataSaver::~DataSaver() {
	// TODO Auto-generated destructor stub
}
void DataSaver::delete_result(int id) {
	this->resultMap.erase(id);
	--result_count;
}
void DataSaver::set_result(int id, unique_ptr<Result> result) {
	resultMap[id] = move(result);
	++result_count;
}
unique_ptr<Result> &DataSaver::get_result(int id) {
	return resultMap[id];
}
void DataSaver::clear() {
	resultMap.clear();
	result_count = 0;
}

void DataSaver::write_result_in_file(int id) {
	std::ofstream out("ClassificationResults.txt");
	out << resultMap[id]->toString();
}

static void ensure_number_of_outputs_matches_classes(const Image &output, const vector<string> &classnames) {
	if (output.size() != classnames.size()) {
		throw Size_missmatch { };
	}
}

static auto make_result(const Image &output, const vector<string> &classnames) {
	ensure_number_of_outputs_matches_classes(output, classnames);
	auto result = make_unique<Result>();
	auto a = output.ptr();
	for (size_t i = 0, n = classnames.size(); i < n; ++i) {
		result->save_result(classnames[i], a[i]);
	}
	return result;
}

void DataSaver::process_output(unique_ptr<Image> output, int id) {
	set_result(id, make_result(*output, classnames));
}

map<int, unique_ptr<Result>> &DataSaver::get_map() {
	return this->resultMap;
}

bool cmp(const pair<string, float> &p1, const pair<string, float> &p2) {
	return p1.second > p2.second;
}

std::vector<pair<std::string, float> > DataSaver::convertToVector(std::map<std::string, float> map) {
	std::vector<pair<std::string, float> > toVector;
	copy(map.begin(), map.end(), back_inserter(toVector));
	sort(toVector.begin(), toVector.end(), cmp);
	return toVector;
}

Result DataSaver::aggregate() {
	//1- each image has 4 class names, add these to one map (globalMap) on this class, total of 4* number of images class names
	//2- if class name already exists in globalMap, add percentage of current image classification
	//3- parse through whole globalMap and select 4 biggest percentages
	//4- divide percentages by 4 and save aggregation as a new Result

	map<string, float> global;
	std::map<int, unique_ptr<Result>>::iterator it;
	for (it = resultMap.begin(); it != resultMap.end(); ++it) {
		//iterate through images
		auto &res = resultMap[it->first];
		if (res != nullptr) {
			for (auto x : res->get_results()) {
				//iterating through results of the image
				if (global.find(x.first) == global.end()) {
					//if classname doesn't exist add it
					global[x.first] = x.second;
				} else {
					//if classname exists, add the new value to it
					global[x.first] += x.second;
				}
				// next classname of the results
			}
		}
	}
	// now global is filled with all the classnames, need to look for the biggest 4

	Result aggregationResult;
	for (auto x : global) {
		global[x.first] = x.second / result_count;
		//divide by number of inputs
	}
	std::vector<pair<std::string, float>> vector = convertToVector(global);
	int number_of_results = 0;
	for (auto x : vector) {
		aggregationResult.save_result(x.first, x.second);
		++number_of_results;
		if (number_of_results >= 4) {
			break;
		}
	}
	return aggregationResult;
}

const char *Size_missmatch::what() const noexcept {
	return "hepics::Size_missmatch";
}

}
