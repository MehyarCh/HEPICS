#include "Result.h"

namespace hepics{

Result::Result() {
}

Result::~Result() {
}

void Result::save_result(string className, float percentage){
	results.push_back(make_pair(className, percentage));
	sort_results();
}

void Result::display_result(){
	for( auto line : results ){
		std::cout << line.first + ": " + std::to_string(line.second) << std::endl;
	}
}

string Result::toString(){
	string result;
	for( auto line : results ){
		result += line.first + ": " + std::to_string(line.second)+ "\n";
	}
	return result;
}
vector<pair<string, float>> &Result::get_results(){
	return this->results;
}
bool sortbysecdesc(const pair<string, float> &a, const pair<string,float> &b) {
       return a.second>b.second;
}
void Result::sort_results(){
	std::sort(results.begin(), results.end(), sortbysecdesc);
}

} //namespace hepics
