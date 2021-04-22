/*
 * Node.cpp
 *
 *  Created on: Apr 14, 2021
 *      Author: James Kraatz
 */

#include "Node.h"

Node::Node() {
	m_key = "";
	m_course = nullptr;
	m_left = nullptr;
	m_right = nullptr;
	m_height = 0;
}

Node::Node(Course* t_course) : Node() {
	this->m_key = t_course->Number();
	this->m_course = t_course;
	this->m_height = 1;
}

Node::~Node() {
	if(this->m_course != nullptr) {
		delete(m_course);
	}
}

std::string Node::key() {
	return this->m_key;
}

Course* Node::course() {
	return this->m_course;
}

Node* Node::left() {
	return this->m_left;
}

Node* Node::right() {
	return this->m_right;
}

int Node::height() {
	return this->m_height;
}

Course* Node::setCourse(Course* t_course) {
	Course* oldCourse = this->m_course;
	this->m_course = t_course;
	this->m_key = t_course->Number();
	return oldCourse;
}

Node* Node::setLeft(Node* t_left) {
	Node* oldLeft = this->m_left;
	this->m_left = t_left;
	return oldLeft;
}

Node* Node::setRight(Node* t_right) {
	Node* oldRight = this->m_right;
	this->m_right = t_right;
	return oldRight;
}

int Node::setHeight(int t_height) {
	int oldHeight = this->m_height;
	this->m_height = t_height;
	return oldHeight;
}

std::string Node::listing() {
	return this->m_course->listing();
}

std::string Node::str() {
	return this->m_course->str();
}
