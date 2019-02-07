/*
 * Section.h
 *
 *  Created on: Feb 4, 2019
 *      Author: ibrahim
 */

#ifndef SRC_SECTION_H_
#define SRC_SECTION_H_

#include "stdlib.h"
#include "List.h"

class Section {
private:
    char *type;
    List *options;

public:
	Section();
	virtual ~Section();

	List* getOptions() const {
		return options;
	}

	void setOptions(List* options) {
		this->options = options;
	}

	char* getType() {
		return type;
	}

	void setType(char* type) {
		this->type = type;
	}
};

#endif /* SRC_SECTION_H_ */
