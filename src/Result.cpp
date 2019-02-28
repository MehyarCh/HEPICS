#include "Result.h"

namespace hepics{

Result::Result() {
	this->i=0;
}

Result::~Result() {
	// TODO Auto-generated destructor stub
}
//needs test
string Result::toString(){
//	return classNames[0]+":"+ to_string(percentage[classNames[0]])
//			+", "+classNames[1]+":"+to_string(percentage[classNames[1]])
//			+", "+classNames[2]+":"+to_string(percentage[classNames[2]])
//			+", "+classNames[3]+":"+to_string(percentage[classNames[3]]);
	return "";
}

void Result::save_result(string className, float percentage){
//	this->percentage[className]=percentage;
//	classNames[i]=className;
//	i++;
//	if(i==4){
//		cout << "results saved";
//	}
}

//returns percentage at index in
float Result::getPercentageOf(string className){
	return percentage[className];
}

//returns index if true, -1 if false
int Result::getClassNameAt(string className){
//	for (int i=0; i<4; ++i){
//		if(classNames[i]==className){
//			return i;
//		}
//	}
	return -1;
}
//map<string, float> Result::getPercentage(){
//	return this->percentage;
//}
} //namespace hepics
