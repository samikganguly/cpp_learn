// center align character pictures
#include <iostream>
#include <string>
#include <algorithm>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::max;

string::size_type center(vector<string>& picture) {
	string::size_type longest = 0;
	for(vector<string>::const_iterator it = picture.begin(); 
		it != picture.end(); ++it) {
		longest = max(longest, it->size());
	}
	for(vector<string>::iterator it = picture.begin(); it != picture.end();
		++it) {
		string::size_type padding = longest - it->size();
		if(padding % 2 == 0) {
			it->insert((string::size_type)0, padding / 2, ' ');
			it->append(padding / 2, ' ');
		} else {
			it->insert((string::size_type)0, padding / 2, ' ');
			it->append(padding / 2 + 1, ' ');
		}
	}
	return longest;
}

int main(void) {
	vector<string> picture;
	string line;
	cout << "Enter character picture(end with EOF)" << endl;
	while(cin) {
		getline(cin, line);
		picture.push_back(line);
	}
	string::size_type longest = center(picture);
	string first_line(longest + 2, '*');
	cout << first_line << endl;
	for(vector<string>::const_iterator it = picture.begin();
		it != picture.end(); ++it) {
		cout << '*' << *it << '*' << endl;
	}
	cout << first_line << endl;
	return 0;
}
