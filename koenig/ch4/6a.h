#ifndef GUARD_6a_h
#define GUARD_6a_h

#include <vector>
#include <stdexcept>

double median(std::vector<double>& hw);
double grade(double midterm, double final_exam, std::vector<double>& hw)
	throw (std::domain_error);

#endif 
