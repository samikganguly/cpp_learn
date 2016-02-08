// word count
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::find;

int main(void) {
	vector<string> words;
	vector<unsigned int> counts;
	string curr_word;
	cout << "Enter words(end by EOF):" << endl;
	while(cin >> curr_word) {
		vector<string>::const_iterator i 
		  = find(words.begin(), words.end(), curr_word);
		if(i == words.end()) {// new input string
			words.push_back(curr_word);
			counts.push_back(1);
		} else {// string is already input
			int index = i - words.begin();
			++counts[index];
		}
	}
	assert(words.size() == counts.size());
	for(vector<string>::size_type i = 0; i < words.size(); i++) {
		cout << words[i] << " occured " << counts[i] << " times" << endl;
	}
}
