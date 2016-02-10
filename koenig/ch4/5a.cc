// count total number of words
#include "5.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main(void) {
	vector<string> words;
	cout << "Enter words(end with EOF): " << endl;
	read_words(cin, words);
	cout << "Total number of words = " << words.size() << endl;
	return 0;
}
