// student grading with list or vector
#include <iostream>
#include <string>
#include <stdexcept>
//#include "2aa.h"
#include "2ab.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::domain_error;
using std::vector;
using std::list;

bool compare(Student_info s1, Student_info s2) {
	return s1.name < s2.name;
}

int main(void) {
	//vector<Student_info> students, fail;
	list<Student_info> students, fail;
	read(cin, students);
	fail = extract_fails(students);
	cout << students.size() << "students passed, "
	     << fail.size() << " student(s) failed." << endl;
	return 0;
}
