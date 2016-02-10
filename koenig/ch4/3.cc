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
	const int largest = 1000;
	const string longest = to_string(largest);
	const string longest_sq = to_string(largest * largest);
	for(int i = 1; i != largest + 1; ++i) {
		cout << "| " << setw(longest.size()) << i << " | "
		     << setw(longest_sq.size()) << i * i << " |" << endl;
	}
	return 0;
}
