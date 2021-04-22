/*
 * Node.h
 *
 *  Created on: Apr 14, 2021
 *      Author: Dell
 */

#ifndef NODE_H_
#define NODE_H_

#include <cstdlib>
#include <string>

#include "Course.h"

class Node{
private:
	std::string m_key;
	Course* m_course;
	Node* m_left;
	Node* m_right;
	int m_height;

	Node();

public:
	Node(Course* t_course);
	virtual ~Node();
	std::string key();
	Course* course();
	Course* setCourse(Course* t_course);
	Node* left();
	Node* setLeft(Node* t_left);
	Node* right();
	Node* setRight(Node* t_right);
	int height();
	int setHeight(int t_height);
	std::string listing();
	std::string str();
};

#endif /* NODE_H_ */
