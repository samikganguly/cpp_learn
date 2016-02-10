// format and align output
#include <iostream>
#include <string>
#include <iomanip>

using std::string;
using std::to_string;
using std::cout;
using std::endl;
using std::setw;

int main(void) {
	const int largest = 100;// changing this to 1000 misaligns the last row
	const string longest = to_string(largest * largest);
	for(int i = 1; i != largest + 1; ++i) {
		cout << "| " << setw(3) << i << " | "
		     << setw(longest.size()) << i * i << " |" << endl;
	}
	return 0;
}
