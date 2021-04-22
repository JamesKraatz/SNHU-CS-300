//============================================================================
// Name        : CS300-Project2.cpp
// Author      : SNHU Student James Kraatz
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "CS300-Project2.h"

int GetMenuChoice() {
	std::string userInput;
	int choiceValue;

	std::getline(std::cin, userInput);
	if(userInput.length() == 1) {
		choiceValue = std::stoi(userInput.c_str());
		if((0 < choiceValue && choiceValue < 4)
				|| (choiceValue == 9)) {
			return choiceValue;
		}
	}
	std::cout << userInput;
	return std::numeric_limits<int>::max();
}

void LoadFile(AVLTree* t_tree, std::string t_file) {
	std::ifstream dataFile;
	std::streampos fileStart;
	std::string line;
	std::string compareString;
	std::stringstream lineBuffer;
	int lineCount = 0;
	bool validLine = true;
	bool courseExists;
	std::string courseNum;
	std::string courseName;
	Course* newCourse;
	std::vector<std::string> courses;


	if (t_tree->root() != nullptr) {
		std::cout << "Data File has already been loaded";
		return;
	}

	dataFile.open(t_file);

	fileStart = dataFile.rdbuf()->pubseekoff(0, dataFile.beg, dataFile.in);

	std::getline(dataFile, line);
	if(line.substr(0, 3).compare("\xEF\xBB\xBF") == 0) {
		dataFile.rdbuf()->pubseekpos(3, dataFile.in);
	} else {
		dataFile.rdbuf()->pubseekpos(0, dataFile.in);
	}

	fileStart = dataFile.tellg();

	// Get all course numbers
	while(!dataFile.eof()) {
		std::getline(dataFile, line, DELIMITER);
		courses.push_back(line);
		std::getline(dataFile, line);
	}

	dataFile.seekg(fileStart);

	while(validLine && dataFile.good()) {
		++lineCount;

		lineBuffer.clear();
		lineBuffer.sync();
		line.clear();

		std::getline(dataFile, line);
		lineBuffer.str(line);

		std::getline(lineBuffer, courseNum, DELIMITER);

		if(lineBuffer.good()) {
			std::getline(lineBuffer, courseName, DELIMITER);
			courseNum = toUpperCase(courseNum);
			newCourse = new Course(courseNum, courseName);
		} else {
			validLine = false;
		}

		while(validLine && !lineBuffer.eof()) {
			std::getline(lineBuffer, courseNum, DELIMITER);
			courseNum = toUpperCase(courseNum);

			courseExists = false;
			for(auto it = courses.begin(); !(it == courses.end() || courseExists); ++it) {
				if(courseNum.compare(*it) == 0) {
					newCourse->AddPreRequisite(courseNum);
					courseExists = true;
				}
			}
			validLine = courseExists;
		}

		if(validLine) {
			t_tree->AddNode(newCourse);
		}
	}

	dataFile.close();

	if(validLine) {
		return;
	}

	std::cout << "Error in data file at line: " << lineCount << std::endl << std::endl;

	delete(newCourse);
	delete(t_tree);
}

bool CourseExists(std::ifstream t_file, std::string t_course) {
	std::streampos bookmark = t_file.tellg();
	bool courseExists = false;
	std::string workingString;

	t_file.seekg(std::ios_base::beg);
	while(t_file.good() && !courseExists) {
		std::getline(t_file, workingString, DELIMITER);
		workingString = toUpperCase(workingString);
		if(workingString.compare(t_course) == 0) {
			courseExists = true;
		}
		std::getline(t_file, workingString);
	}

	t_file.seekg(bookmark);

	return courseExists;
}

std::string toUpperCase(std::string t_string) {
	std::transform(t_string.begin(),t_string.end(), t_string.begin(), toupper);
	return t_string;
}

int main(int argc, char* argv[]) {
	int command;
	std::string course;
	std::string fileName;
	AVLTree tree = AVLTree();

	// if data file provided on command line load it else load default file
	if (argc == 2) {
		fileName = argv[1];
	} else {
		fileName = DEFAULTFILE;
	}

	std::cout << std::endl;
	std::cout << "Welcome to the course planner." << std::endl;

	// start main loop
	while(true) {
		// show menu
		std::cout << MAINMENU;
		// get response
		command = GetMenuChoice();
		// process response
		switch(command) {
		case 1 :	// load data file
			std::cout << "Loading data file " << std::endl;
			LoadFile(&tree, fileName);
			break;
		case 2 :	// display sample schedule
			std::cout << "Here is a sample schedule: " << std::endl;
			if(tree.root() != nullptr) {
				std::cout << std::endl;
				tree.PrintList();
			} else {
				std::cout << "You must load data file first." << std::endl;
			}
			break;
		case 3 :	// display a course
			std::cout << std::endl << "What course do you want to know about? ";
			std::getline(std::cin, course);

			course = toUpperCase(course);

			if(tree.root() != nullptr) {
				Node* courseToPrint = tree.FindNode(course);
				if(courseToPrint != nullptr) {
					std::cout << courseToPrint->course()->str() << std::endl;
				} else {
					std::cout << "Course: " << course
							<< " not found." << std::endl;
				}
			} else {
				std::cout << "You must load data file first." << std::endl;
			}
			break;
		case 9 :	// exit program
			std::cout << std::endl << "Thank You for using the course planner!" << std::endl;
			return 0;
		default:	// all other entries are invlaid
			std::cout << " is not a valid option." << std::endl;
			break;
		}
	}
	// should never get here, if so return -1 to signify error
	return -1;
}
