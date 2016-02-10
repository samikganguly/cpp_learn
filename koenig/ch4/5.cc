// implementation of read_words
#include "5.h"

using std::istream;
using std::vector;
using std::string;

istream& read_words(istream& is, vector<string>& words) {
	if(is) {
		words.clear();
		string word;
		while(is >> word)
			words.push_back(word);
		is.clear();
	}
	return is;
}
