// writes lowercase words followed by uppercase words
#include <iostream>
#include <list>
#include <cctype>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::isupper;
using std::islower;

int main(void) {
	string word;
	char w;
	list<string> words, upper, lower;
	cout << "Enter words in uppercase or lowercase(end with EOF)" << endl;
	while(cin >> word) {
		if(!word.empty())
			words.push_back(word);
	}
	for(list<string>::iterator i = words.begin(); i != words.end();) {
		string word = *i;
		bool fully_cased = true;
		const bool wupper = isupper(word[0]);
		for(string::size_type i = 0; i != word.size(); ++i) {
			if((wupper && islower(word[i]))
			  || (!wupper && isupper(word[i]))) {
				fully_cased = false;
				break;
			}
		}
		if(fully_cased) {
			if(wupper) upper.push_back(word);
			else lower.push_back(word);
		}
		i = words.erase(words.begin());
	}
	cout << "Lowercased words\n"
	     << "----------------" << endl;
	for(string word:lower)
		cout << word << endl;
	cout << "Uppercased words\n"
	     << "----------------" << endl;
	for(string word:upper)
		cout << word << endl;
	return 0;
}
