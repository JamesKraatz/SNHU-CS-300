/*
 * Course.cpp
 *
 *  Created on: Apr 14, 2021
 *      Author: James Kraatz
 */

#include "Course.h"

Course::Course() {
	m_courseNum = "";
	m_name = "";
}

Course::Course(std::string t_courseNum) : Course() {
	transform(t_courseNum.begin(), t_courseNum.end(), t_courseNum.begin(), toupper);
	m_courseNum = t_courseNum;
}

Course::Course(std::string t_courseNum, std::string t_name) : Course(t_courseNum) {
	m_name = t_name;
}

Course::~Course() {
}

void Course::AddPreRequisite(std::string t_courseNum) {
	for (std::vector<std::string>::iterator it = m_preRequisites.begin();
			it != m_preRequisites.end(); ++it) {
		if (t_courseNum.compare(*it) < 0) {
			m_preRequisites.insert(it, t_courseNum);
			return;
		}
	}
	m_preRequisites.push_back(t_courseNum);
}

std::string Course::Number() {
	return m_courseNum;
}

std::string Course::Name() {
	return m_name;
}

std::string Course::PreRequisites() {
	std::stringstream preReqList;

	if(this->m_preRequisites.size() == 0) {
		preReqList << "None";
	}

	for(auto preReq = std::begin(this->m_preRequisites);
			preReq != std::end(this->m_preRequisites); ++preReq) {
		preReqList << *preReq;

		if(std::next(preReq) != std::end(this->m_preRequisites)) {
			preReqList << ", ";
		}
	}

	return preReqList.str();
}

std::string Course::listing() {
	std::stringstream listing;
	listing << this->m_courseNum << ", " << this->m_name;

	return listing.str();
}

std::string Course::str() {
	std::stringstream course;
	course << this->listing() << std::endl;
	course << "Prerequisites: " << this->PreRequisites() << std::endl;

	course << std::endl;

	return course.str();
}
