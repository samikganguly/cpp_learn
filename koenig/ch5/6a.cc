#include "2aa.h"
#include "2b.h"

using std::vector;
using std::string;
using std::istream;
using std::domain_error;

istream& read_hw(istream& in, vector<double>& hw) {
	if(in) {
		hw.clear();
		double g;
		while(in >> g) {
			hw.push_back(g);
		}
		in.clear();
	}
	return in;
}

istream& read(istream& in, vector<Student_info>& students) {
	Student_info student;
	while(in >> student.name) {
		in  >> student.midterm >> student.final_exam;
		read_hw(in, student.hw);
		students.push_back(student);
	}
	return in;
}

vector<Student_info> extract_fails(vector<Student_info>& students) {
	vector<Student_info> fail;
	double s_grade;
	vector<Student_info>::size_type pass_cnt = 0;
	for(vector<Student_info>::size_type i = 0;
	    i < students.size(); ++i) {
		try {
			s_grade = grade(students[i].midterm,
		                        students[i].final_exam,
		                        students[i].hw);
		} catch(domain_error) {
			s_grade = 0;
		}
		if(fgrade(s_grade)) {
			fail.push_back(students[i]);
		} else {
			students.insert(students.begin(), students[i]);
			++i;
			++pass_cnt;
		}
	}
	students.resize(pass_cnt);
	return fail;
}
