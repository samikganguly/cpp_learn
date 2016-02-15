#ifndef GUARD_3a_h
#define GUARD_3a_h

#include <iostream>
#include <string>
#include <vector>
#include <list>

struct Student_info {
	std::string name;
	double midterm, final_exam;
	std::vector<double> hw;
};
std::istream& read(std::istream& is, std::vector<Student_info>& students);
std::istream& read_hw(std::istream& is, std::vector<double>& hw);
std::vector<Student_info> extract_fails(std::vector<Student_info>& students);
std::istream& read(std::istream& is, std::list<Student_info>& students);
std::list<Student_info> extract_fails(std::list<Student_info>& students);

#endif
