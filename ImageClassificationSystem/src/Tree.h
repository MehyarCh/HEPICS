/*
 * Tree.h
 *
 *  Created on: Feb 3, 2019
 *      Author: ibrahim
 */

#ifndef SRC_TREE_H_
#define SRC_TREE_H_

class Tree {
private:
    int *leaf;
    int n;
    int *parent;
    int *child;
    int *group;
    char **name;

    int groups;
    int *group_size;
    int *group_offset;

public:
	Tree();
	virtual ~Tree();
};

#endif /* SRC_TREE_H_ */
