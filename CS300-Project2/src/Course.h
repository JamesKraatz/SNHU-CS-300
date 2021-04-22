/*
 * Course.h
 *
 *  Created on: Apr 14, 2021
 *      Author: Dell
 */

#ifndef COURSE_H_
#define COURSE_H_

#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>

class Course {
private:

	std::string m_courseNum;
	std::string m_name;
	std::vector<std::string> m_preRequisites;
	Course();
	Course(std::string t_courseNum);

public:
	Course(std::string t_courseNum, std::string t_name);
	virtual ~Course();
	void AddPreRequisite(std::string t_courseNum);
	std::string Number();
	std::string Name();
	std::string PreRequisites();
	std::string listing();
	std::string str();
};

#endif /* COURSE_H_ */
