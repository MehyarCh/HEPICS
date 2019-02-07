/*
 * Node.h
 *
 *  Created on: Feb 1, 2019
 *      Author: ibrahim
 */

#ifndef SRC_NODE_H_
#define SRC_NODE_H_

#include <stdlib.h>

class Node {
private:
    void *val;
    Node *next;
    Node *prev;
public:
	Node();
	virtual ~Node();

	Node* getNext() const {
		return next;
	}

	void setNext(Node* next) {
		this->next = next;
	}

	Node* getPrev() const {
		return prev;
	}

	void setPrev(Node* prev) {
		this->prev = prev;
	}

	void* getVal() const {
		return val;
	}

	void setVal(void* val) {
		this->val = val;
	}
};

#endif /* SRC_NODE_H_ */
