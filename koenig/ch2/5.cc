// program to make a square, a rectangle and a triangle with *
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(void) {
	const int side = 5;
	const int width = 5;
	const int length = 10;
	const int height = 5;
	const int base = 9;
	cout << "Square" << endl;
	for(int r = 0; r != side; r++) {
		for(int c = 0; c != side; c++) {
			if(r == 0 || r == side - 1 || c == 0 || c == side - 1)
				cout << '*';
			else
				cout << ' ';
		}
		cout << endl;
	}
	cout << "Rectangle" << endl;
	for(int r = 0; r != width; r++) {
		for(int c = 0; c != length; c++) {
			if(r == 0 || r == width - 1 
			   || c == 0 || c == length - 1)
				cout << '*';
			else
				cout << ' ';
		}
		cout << endl;
	}
	cout << "Triangle" << endl;
	for(int r = 0; r != height; r++) {
		for(int c = 0; c != base; c++) {
			if(r == height - 1 || c == base / 2 - r 
			   || c == base / 2 + r)
				cout << '*';
			else
				cout << ' ';
		}
		cout << endl;
	}	
	return 0;
}
