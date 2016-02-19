// student grading with list or vector
#include <iostream>
#include <string>
#include <stdexcept>
#include "6a.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::domain_error;
using std::vector;

typedef vector<Student_info> records;

int main(void) {
	records students, fail;
	read(cin, students);
	fail = extract_fails(students);
	cout << students.size() << "students passed, "
	     << fail.size() << " student(s) failed." << endl;
	return 0;
}
