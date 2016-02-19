#ifndef GUARD_6a_h
#define GUARD_6a_h

#include <iostream>
#include <string>
#include <vector>

struct Student_info {
	std::string name;
	double midterm, final_exam;
	std::vector<double> hw;
};
std::istream& read(std::istream& is, std::vector<Student_info>& students);
std::istream& read_hw(std::istream& is, std::vector<double>& hw);
std::vector<Student_info> extract_fails(std::vector<Student_info>& students);

#endif
