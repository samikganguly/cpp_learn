// count number of each word
#include "5.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main(void) {
	vector<wc_map> words;
	cout << "Enter words(end with EOF): " << endl;
	read_words(cin, words);
	for(vector<wc_map>::size_type i = 0; i != words.size(); ++i) {
		cout << words[i].word << " = " << words[i].count << endl;
	}
	return 0;
}
