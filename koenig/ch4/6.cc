// calculate and display student name and grades
// input format:
// <student name> <midterm grade> <final exam grade> <homework grades><EOF>

#include <iostream>
#include <ios>
#include <iomanip>
#include <string>
#include <algorithm>
#include "6b.h"
#include "6a.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::setw;
using std::setprecision;
using std::streamsize;
using std::string;
using std::vector;
using std::max;

string::size_type longest_name;
bool compare_students(Student_info& s1, Student_info& s2) {
	longest_name = max(max(longest_name, s1.name.size()), s2.name.size());
	return s1.name < s2.name;
}
int main(void) {
	vector<Student_info> students;
	char another = 'y';
	cout << "Enter student's name, mid-term grade, final exam "
		"grade and all the homework grades separated with "
		"spaces" << endl;
	while(another == 'y' || another == 'Y') {
		read(cin, students);
		cout << "Do you want to enter records for another student?"
		        "(y/n) ";
		cin >> another;
	}
	sort(students.begin(), students.end(), compare_students);
	streamsize prec = cout.precision(3);
	for(vector<Student_info>::size_type i = 0; i < students.size(); ++i) {
		cout << setw(longest_name) << students[i].name << "\t"
		     << students[i].final_grade << endl;
	}
	cout.precision(prec);
	return 0;
}
