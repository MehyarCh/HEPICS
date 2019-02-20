/*
 * Node.cpp
 *
 *  Created on: Feb 1, 2019
 *      Author: ibrahim
 */

#include "Node.h"

Node::Node() {
}

void free_node(Node *n)
{
	Node *next;
	while(n) {
		next = n->getNext();
		free(n);
		n = next;
	}
}

Node::~Node() {
	free_node(this);
}

