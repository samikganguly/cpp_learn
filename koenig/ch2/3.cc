// show a greeting with variable padding, separate padding lengths for 
// row and column, padding amout in entered by user
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(void) {
	string name;
	int hpadding;
	int vpadding;
	cout << "Enter your first name: ";
	cin >> name;
	cout << "Enter horizontal padding in number of columns: ";
	cin >> hpadding;
	cout << "Enter vertical padding in number of rows: ";
	cin >> vpadding;
	const string greeting = "Hello, " + name + "!";
	const int rows = vpadding * 2 + 3;
	const string::size_type cols = greeting.size() + hpadding * 2 + 2;
	for(int r = 0; r != rows; r++) {
		string::size_type c = 0; 
		while(c != cols) {
			if(r == vpadding + 1 && c == hpadding + 1) {
				cout << greeting;
				c += greeting.size();
			} else {
				if(r == 0 || r == rows - 1 
				   || c == 0 || c == cols - 1)
					cout << '*';
				else
					cout << ' ';
				c++;
			}
		}
		cout << endl;
	}
	return 0;
}
