#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>


namespace hepics{
using std::vector;
using std::string;
using std::pair;
using std::map;

class Result {
private:
	vector<pair<string, float>> results;
public:
	Result();
	virtual ~Result();

	void save_result(string className, float percentage);
	void display_result();

	string toString();

	vector<pair<string, float>> &get_results();

	void sort_results();
};
} //namespace hepics
