#include <string>
#include "3b.h"

using std::string;
using std::vector;
using std::domain_error;

double median(vector<double>& hw) {
	const vector<double>::size_type sz = hw.size();
	if(sz > 0)
		return (sz % 2 == 0) ? (hw[sz / 2 - 1] + hw[sz / 2]) / 2
			: hw[sz / 2];
	else
		return 0;
}
double grade(double midterm, double final_exam, vector<double>& hw)
	throw (domain_error) {
	if(hw.size() == 0)
		throw domain_error("student has done no homework");
	return 0.2 * midterm + 0.4 * final_exam + 0.4 * median(hw);
}
