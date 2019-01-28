/*
 * DataSaver.h
 *
 *  Created on: Jan 15, 2019
 *      Author: Mehyar
 */

#ifndef DATASAVER_H_
#define DATASAVER_H_
#include "Result.h"
#include "Image.h"

using namespace std;

class DataSaver {
private:
	std::map<int,Result> resultMap;
public:
	DataSaver();
	virtual ~DataSaver();
	void addResult(Image input, Result result);
	void setResult(Image input, Result result);
	Result getResult(Image input);
	void writeResultInFile(Image input);

};

#endif /* DATASAVER_H_ */
