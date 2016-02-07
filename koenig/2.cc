// print the quartiles
#include <iostream>
#include <ios>
#include <iomanip>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::sort;
using std::streamsize;
using std::setprecision;
using std::fixed;

int main(void) {
	double num;
	double quartiles[3];
	vector<double> numbers;
	cout << "Enter numbers(end with EOF): " << endl;
	while(cin >> num) {
		numbers.push_back(num);
	}
	sort(numbers.begin(), numbers.end());
	vector<double>::size_type numbers_sz = numbers.size();
	if(numbers_sz < 4) {
		cout << "Enter at least 4 numbers" << endl;
		return 1;
	}
	streamsize prec = cout.precision();
	if(numbers_sz % 2 == 0) {
		quartiles[1] = (numbers[numbers_sz / 2 - 1] 
		             + numbers[numbers_sz / 2]) / 2;
	} else {
		quartiles[1] = numbers[numbers_sz / 2];
	}
	if(numbers_sz % 4 == 1) {
		quartiles[0] = numbers[numbers_sz / 4 - 1] / 4
		             + numbers[numbers_sz / 4] * 3 / 4;
		quartiles[2] = numbers[numbers_sz / 4 * 3] / 4 * 3
		             + numbers[numbers_sz / 4 * 3 + 1] / 4;
	} else if(numbers_sz % 4 == 3) {	
		quartiles[0] = numbers[numbers_sz / 4] * 3 / 4
		             + numbers[numbers_sz / 4 + 1] / 4;
		quartiles[2] = numbers[numbers_sz / 4 * 3 + 1] / 4
		             + numbers[numbers_sz / 4 * 3 + 2] / 4 * 3;
	} else {
		quartiles[0] = numbers[numbers_sz / 4];
		quartiles[2] = numbers[numbers_sz / 4 * 3 + 1];
	}
	cout << fixed << setprecision(3) << "1st quartile = " << quartiles[0]
	     << ", 2nd quartile = " << quartiles[1] << ", 3rd quartile = "
	     << quartiles[2] << setprecision(prec) << endl;
	return 0;
}
