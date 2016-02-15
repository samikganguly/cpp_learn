#include "6b.h"
#include "6a.h"

using std::istream;
using std::vector;
using std::string;
using std::domain_error;
using std::cerr;
using std::endl;

istream& read_hw(istream& is, vector<double>& hw) {
	if(is) {
		hw.clear();
		double h;
		while(is >> h)
			hw.push_back(h);
		is.clear();
	}
	return is;
}
istream& read(istream& is, vector<Student_info>& students) {
	Student_info stud;
	vector<double> hw;
	double midterm, final_exam;
	is >> stud.name >> midterm >> final_exam;
	read_hw(is, hw);
	try {
		stud.final_grade = grade(midterm, final_exam, hw);
		students.push_back(stud);
	} catch(domain_error e) {
		cerr << e.what() << endl;
	}
	return is;
}
