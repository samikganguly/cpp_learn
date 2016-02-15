#include "3a.h"
#include "3b.h"

using std::vector;
using std::list;
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
	for(vector<Student_info>::size_type i = 0;
	    i < students.size();) {
		try {
			s_grade = grade(students[i].midterm,
		                        students[i].final_exam,
		                        students[i].hw);
		} catch(domain_error) {
			s_grade = 0;
		}
		if(fgrade(s_grade)) {
			fail.push_back(students[i]);
			students.erase(students.begin() + i);
		} else {
			++i;
		}
	}
	return fail;
}

istream& read(istream& in, list<Student_info>& students) {
	Student_info student;
	while(in >> student.name) {
		in  >> student.midterm >> student.final_exam;
		read_hw(in, student.hw);
		students.push_back(student);
	}
	return in;
}

list<Student_info> extract_fails(list<Student_info>& students) {
	list<Student_info> fail;
	double s_grade;
	for(list<Student_info>::iterator it = students.begin();
	    it != students.end();) {
		try {
			s_grade = grade(it->midterm, 
			                it->final_exam,
					it->hw);
		} catch(domain_error) {
			s_grade = 0;
		}
		if(fgrade(s_grade)) {
			fail.push_back(*it);
			it = students.erase(it);
		} else {
			++it;
		}
	}
	return fail;
}
