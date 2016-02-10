// grades of multiple students
#include <iostream>
#include <ios>
#include <iomanip>
#include <string>
#include <vector>
#include <cassert>

using std::cin;
using std::cout;
using std::endl;
using std::ws;
using std::string;
using std::vector;
using std::setprecision;
using std::streamsize;

int main(void) {
	string name;
	double midterm;
	double final_exam;
	double homework;
	double homework_avg;
	int n_homeworks;
	char cont = 'y';
	vector<string> student_names;
	vector<double> final_grades;
	while(cont == 'y' || cont == 'Y') {
		midterm = final_exam = homework 
		        = homework_avg = n_homeworks = 0;
		cout << "Enter student name: ";
		// consume any whitespace from previous iteration
		// as getline doesn't discard leading whitespace
		cin >> ws;
		// reading the full name
		if(std::getline(cin, name))
			student_names.push_back(name);
		cout << "Enter midterm and final exam grades of " 
		     << name << ":" << endl;
		cin >> midterm >> final_exam;
		cout << "Enter homework grades of "
		     << name << ":(end with EOF)" << endl;
		while(cin >> homework) {
			homework_avg += homework;
			++n_homeworks;
		}
		// EOF sets the eofbit in cin
		// clear the stream for next input
		cin.clear();
		if(n_homeworks != 0)
			homework_avg /= n_homeworks;
		final_grades.push_back(0.4 * midterm + 0.2 * final_exam
		                      + 0.4 * homework_avg);
		cout << "Enter records of another student?(y/n) ";
		cin >> cont;
	}
	assert(student_names.size() == final_grades.size());
	streamsize prec = cout.precision();
	for(vector<double>::size_type i = 0; i < student_names.size(); i++) {
		cout << "Final grade of " << student_names[i] << "="
		     << setprecision(3) << final_grades[i] << setprecision(prec)
		     << endl;
	}
	return 0;
}
