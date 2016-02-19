#ifndef GUARD_6b_h
#define GUARD_6b_h

#include <vector>
#include <stdexcept>

double median(std::vector<double>& hw);
double grade(double midterm, double final_exam, std::vector<double>& hw)
	throw (std::domain_error);
inline bool fgrade(double grade) {
	return grade < 60;
}

#endif 
