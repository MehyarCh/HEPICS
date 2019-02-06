/*
 * Options_list.cpp
 *
 *  Created on: Feb 2, 2019
 *      Author: ibrahim
 */

#include "Options_list.h"

Options_list::Options_list(char *key, char *val) {
    this->key = key;
    this->val = val;
    this->used = 0;
}

Options_list::~Options_list() {
	free(this);
}

