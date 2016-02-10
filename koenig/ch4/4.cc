// format and align output
#include <iostream>
#include <string>
#include <iomanip>

using std::string;
using std::to_string;
using std::cout;
using std::endl;
using std::setw;
using std::streamsize;
using std::fixed;

int main(void) {
	const double largest = 10;
	const int precision = 2;
	const streamsize prec = cout.precision(precision);
	const long int_largest = largest;// take the integral part
	const string longest = to_string(int_largest);
	const string longest_sq = to_string(int_largest * int_largest);
	for(double i = 1; i <= largest; i += 0.01) {
		cout << fixed << "| " << setw(longest.size() + precision + 1) 
		     << i << " | " << setw(longest_sq.size() + precision + 1)
		     << i * i << " |" << endl;
	}
	cout.precision(precision);
	return 0;
}
