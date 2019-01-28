/*
 * Result.h
 *
 *  Created on: Jan 22, 2019
 *      Author: Mehyar
 */

#ifndef MODEL_RESULT_H_
#define MODEL_RESULT_H_
#include <map>
#include <vector>
using namespace std;

class Result {
private:
	int i;
	map<string, float> percentage;
	vector<string> classNames;
public:
	Result();
	virtual ~Result();
	string toString();
	void saveResult(float percentage, string className);
	//returns percentage at index in
	float getPercentageOf(string className);
	//returns index if true, -1 if false
	int getClassNameAt(string className);

};

#endif /* MODEL_RESULT_H_ */
