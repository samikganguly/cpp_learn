// generate permuted index
#include <iostream>
#include <string>
#include <iomanip>
#include <list>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::left;
using std::right;
using std::setw;
using std::list;

list<string> split(string& str) {
	list<string> ret;
	typedef string::const_iterator s_iter;
	for(s_iter i = str.begin(), j = i; i != str.end();) {
		while(isspace(*i)) ++i;
		j = i;
		while(!isspace(*j) && j != str.end()) ++j;
		if(i != j) {
			string word(i,j);
			ret.push_back(word);
		}
		i = j;
	}
	return ret;
}

// returns true if the permutation is complete
bool permute(list<string>& words, const string& marker) {
	static bool complete = true;
	if(complete) {
		words.push_back(marker);
		complete = false;
	}
	string head = *(words.begin());
	words.erase(words.begin());
	words.push_back(head);
	if(head == marker)
		complete = true;
	return complete;
}

int main(void) {
	string line, marker = "\n";
	list<string> words;
	cout << "Enter a phrase: " << endl;
	std::getline(cin, line);
	string::size_type line_sz = line.size();
	words = split(line);
	line.clear();
	bool complete = permute(words, marker);
	while(!complete) {
		typedef list<string>::const_iterator s_iter;
		s_iter i;
		cout << right << setw(line_sz);
		for(i = words.begin(); *i != marker; ++i);
		for(++i; i != words.end(); ++i) {
			line += *i + " ";
		}
		cout << line << '\t' << left << setw(line_sz);
		line.clear();
		for(i = words.begin(); *i != marker; ++i) {
			line += *i + " ";
		}
		cout << line << endl;
		line.clear();
		complete = permute(words, marker);
	}
	return 0;
}
