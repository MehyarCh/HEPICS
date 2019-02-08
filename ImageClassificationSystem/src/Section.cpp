/*
 * Section.cpp
 *
 *  Created on: Feb 4, 2019
 *      Author: ibrahim
 */

#include "Section.h"

Section::Section() {
}

Section::~Section() {
	free(this);
}

