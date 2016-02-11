// count total number of words
#include "5.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main(void) {
	vector<wc_map> words;
	vector<wc_map>::size_type count = 0;
	cout << "Enter words(end with EOF): " << endl;
	read_words(cin, words);
	for(vector<wc_map>::size_type i = 0; i != words.size(); i++) {
		count += words[i].count;
	}
	cout << "Total number of words = " << count << endl;
	return 0;
}
