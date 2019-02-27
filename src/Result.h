#pragma once

#include <string>
#include <vector>
#include <map>


namespace hepics{
using std::vector;
using std::string;
using std::pair;
using std::map;

class Result {
private:
	int i;
	map<string, float> percentage;
	vector<pair<string, float>> results;
public:
	Result();
	virtual ~Result();
	string toString();
	void save_result(string className, float percentage);

	//returns percentage at index in
	float getPercentageOf(string className);

	//returns index if true, -1 if false
	int getClassNameAt(string className);
	map<string, float> &getPercentage();
};
}
