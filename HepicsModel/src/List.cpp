/*
 * List.cpp
 *
 *  Created on: Feb 3, 2019
 *      Author: ibrahim
 */

#include "List.h"

List::List() {
	this->size = 0;
	this->front = 0;
	this->back = 0;

}

void free_list(List *l)
{
	l->getFront()->~Node();
	free(l);
}

List::~List() {
	free_list(this);
}

void List::list_insert(void *val) {
	Node *new_node = new Node();
	new_node->setVal(val);
	new_node->setNext(0);

	if(!this->back){
		this->front = new_node;
		new_node->setPrev(0);
	}else{
		this->back->setNext(new_node);
		new_node->setPrev(this->back);
	}
	this->back = new_node;
	++this->size;
}

void** List::list_to_array() {
    void **a = (void **)calloc(this->size, sizeof(void*));
    int count = 0;
    Node *n = this->front;
    while(n){
        a[count++] = n->getVal();
        n = n->getNext();
    }
    return a;
}
