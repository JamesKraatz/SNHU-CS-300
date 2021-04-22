/*
 * CS300-Project2.h
 *
 *  Created on: Apr 16, 2021
 *      Author: Dell
 */

#ifndef CS300_PROJECT2_H_
#define CS300_PROJECT2_H_

#include <cstdlib>
#include <iostream>
#include <limits>
#include <algorithm>
#include <fstream>
#include <string>
#include <iterator>

#include "AVLTree.h"
#include "Node.h"
#include "Course.h"

int GetMenuChoice();
void LoadFile(AVLTree* t_tree, std::string t_file);
bool CourseExists(std::ifstream t_file, std::string t_course);
std::string toUpperCase(std::string t_string);

const char DELIMITER = ',';
const std::string DEFAULTFILE = "ABCU_Advising_Program_Input.txt";

const char* MAINMENU = R"mainMenu(
  1) Load Data Structure.   
  2) Print Course List.     
  3) Print Course.          
  9) Exit.                  

What would you like to do? )mainMenu";

#endif /* CS300_PROJECT2_H_ */
