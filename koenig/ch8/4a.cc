#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <algorithm>
#include "4.h"

using std::cout;
using std::cin;
using std::endl;
using std::list;
using std::string;
using std::copy;
using std::istream_iterator;
using std::ostream_iterator;
using std::back_inserter;

int main(void) {
	string word;
	list<string> words;
	using iter = list<string>::iterator;
	cout << "Enter words(end with EOF)" << endl;
	copy(istream_iterator<string>(cin), istream_iterator<string>(),
		back_inserter(words));
	ch8::reverse(words.begin(), words.end());
	cout << "Reverse order of input" << endl;
	copy(words.begin(), words.end(), ostream_iterator<string>(cout, "\n"));
	return 0;
}
