#ifndef GUARD_6b_h
#define GUARD_6b_h

#include <iostream>
#include <string>
#include <vector>

struct Student_info {
	std::string name;
	double final_grade;
};
std::istream& read(std::istream& is, std::vector<Student_info>& students);
std::istream& read_hw(std::istream& is, std::vector<double>& hw);

#endif
