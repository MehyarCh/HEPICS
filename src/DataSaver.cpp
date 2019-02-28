#include "DataSaver.h"
namespace hepics{
DataSaver::DataSaver() {
}

DataSaver::~DataSaver() {
	// TODO Auto-generated destructor stub
}
void DataSaver::add_result(int id, unique_ptr<Result> result){
	//resultMap.insert(std::make_pair(id,move(result)));
	//resultMap[id] = std::make_unique<Result>();
	resultMap.emplace(id, move(result));
}
void DataSaver::delete_result(int id){
	this->resultMap.erase(id);
}
void DataSaver::set_result(int id, unique_ptr<Result> result){
	resultMap.insert(std::make_pair(id,move(result)));
}
unique_ptr<Result> &DataSaver::get_result(int id){
	return resultMap[id];
}
void DataSaver::write_result_in_file(int id){
	std::ofstream out("ClassificationResults.txt");
	out << resultMap[id]->toString();
}

void DataSaver::add_output(unique_ptr<Image> &&output){
		this->outputs.push_back(move(output));
}
vector<unique_ptr<Image>> &DataSaver::getOutputs(){
	return outputs;
}
bool cmp(const pair<string, float>  &p1, const pair<string, float> &p2){
    return p1.second > p2.second;
}

std::vector<pair<std::string, float> > DataSaver::convertToVector(std::map<std::string,float> map){
	std::vector<pair<std::string, float> > toVector;
	copy(map.begin(), map.end(), back_inserter(toVector));
	sort(toVector.begin(), toVector.end(), cmp);
	return toVector;
}

Result DataSaver::aggregate(){
	//1- each image has 4 class names, add these to one map (globalMap) on this class, total of 4* number of images class names
	//2- if class name already exists in globalMap, add percentage of current image classification
	//3- parse through whole globalMap and select 4 biggest percentages
	//4- divide percentages by 4 and save aggregation as a new Result

	map<string,float> global;
	std::map<int,unique_ptr<Result>>::iterator it;
	for (it = resultMap.begin() ; it != resultMap.end(); ++it){
		//iterate through images
		for (auto x: resultMap[it->first]->get_results()) {
			//iterating through results of the image
			if( global.find(x.first) == global.end()){
				//if classname doesn't exist add it
				global[x.first]= x.second;
			} else {
				//if classname exists, add the new value to it
				global[x.first] += x.second;
			}
			// next classname of the results
		}
	}
	// now global is filled with all the classnames, need to look for the biggest 4


	Result aggregationResult;
	for(auto x : global){
		global[x.first]=x.second/resultMap.size();
		//divide by number of inputs
	}
	std::vector<pair<std::string, float>> vector = convertToVector(global);
	for(auto x : vector) {
	    aggregationResult.save_result(x.first, x.second);
	}
	return aggregationResult;
}

}
