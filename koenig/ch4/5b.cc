// count number of each word
#include <algorithm>
#include <iterator>
#include "5.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::sort;
using std::iterator;

int main(void) {
	vector<string> words;
	string prev, curr;
	cout << "Enter words(end with EOF): " << endl;
	read_words(cin, words);
	sort(words.begin(), words.end());
	vector<string>::size_type count = 0;
	for(vector<string>::size_type i = 0;
	    i != words.size(); ++i) {
		if(i == 0) {
			prev = curr = words[i];
		} else {
			curr = words[i];
		}
		if(prev != curr) {
			cout << prev << " = " << count << endl;
			count = 1;
			prev = curr;
		} else {
			++count;
		}
	}
	if(curr != "")
		cout << curr << " = " << count << endl;
	return 0;
}
