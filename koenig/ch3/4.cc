// longest and shortest string
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(void) {
	string::size_type longest_sz = 0;
	string::size_type shortest_sz = 0;
	string longest = "";
	string shortest = "";
	string word;
	cout << "Enter words(end by EOF):" << endl;
	while(cin >> word) {
		if(shortest == "") {
			shortest = word;
			shortest_sz = shortest.size();
		}
		if(longest == "") {
			longest = word;
			longest_sz = longest.size();
		}
		if(word.size() > longest_sz) {
			longest = word;
			longest_sz = longest.size();
		} else if(word.size() < shortest_sz) {
			shortest = word;
			shortest_sz = shortest.size();
		}
	}
	cout << "shortest word = " << shortest << "(" << shortest_sz 
	     << "letters)" << ", longest word = " << longest << "("
	     << longest_sz << "letters)"<< endl;
	return 0;
}
