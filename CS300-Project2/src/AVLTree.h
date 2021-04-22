/*
 * AVLTree.h
 *
 *  Created on: Apr 14, 2021
 *      Author: Dell
 */

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <cstdlib>
#include <iostream>

#include "Node.h"

class AVLTree {
private:
	Node* m_root;

	void DeleteTree(Node* t_node);
	Node* DeleteNode(Node* t_node, std::string t_key);
	Node* InsertNode(Node* t_node, Course* t_course);
	Node* SearchNode(Node* t_node, std::string t_key);
	Node* RotateLeft(Node* t_node);
	Node* RotateRight(Node* t_node);
	Node* MinValNode(Node* t_node);
	int maxHeight(Node* t_node);
	int getBalance(Node* t_node);
	void ShowTree(Node* t_node);
public:
	AVLTree();
	virtual ~AVLTree();
	Node* AddNode(Course* t_course);
	Node* RemoveNode(std::string t_key);
	Node* FindNode(std::string t_key);
	void PrintList();
	void PrintList(Node* t_node);
	Node* MinNode();
	Node* root();
};

#endif /* AVLTREE_H_ */
