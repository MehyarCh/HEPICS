/*
 * List.h
 *
 *  Created on: Feb 3, 2019
 *      Author: ibrahim
 */

#ifndef SRC_LIST_H_
#define SRC_LIST_H_

#include <stdlib.h>
#include "Node.h"

class List {
private:
    int size;
    Node *front;
    Node *back;
public:
	List();
	virtual ~List();
	void list_insert(void *val);
	void **list_to_array();

	Node* getBack() const {
		return back;
	}

	void setBack(Node* back) {
		this->back = back;
	}

	Node* getFront() {
		return front;
	}

	void setFront(Node* front) {
		this->front = front;
	}

	int getSize() const {
		return size;
	}

	void setSize(int size) {
		this->size = size;
	}
};

#endif /* SRC_LIST_H_ */
