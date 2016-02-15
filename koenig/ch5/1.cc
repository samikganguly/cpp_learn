// generate permuted index
#include <iostream>
#include <string>
#include <iomanip>

using std::string;
using std::cin;
using std::cout;
//using std::clog;
using std::endl;
using std::setw;
using std::left;
using std::right;

// returns the position of the marker
// returns string::npos if the permutation is complete
string::size_type permute(string& str) {
	static string::size_type pos = string::npos;
	if(pos == string::npos) {
		pos = str.size() - 1;
	} else {
		string::size_type next_word = str.rfind(" ", pos);
		if(next_word != string::npos)
			pos = next_word - 1;
		else
			pos = string::npos;
	}
	return pos;
}

int main(void) {
	string line;
	cout << "Enter a phrase: " << endl;
	std::getline(cin, line);
	string::size_type line_sz = line.size();
	string::size_type pos = permute(line);
	while(pos != string::npos) {
		//clog << pos << endl;
		cout << right << setw(line_sz) << line.substr(0, pos + 1) << "\t"
		     << left << setw(line_sz) << line.substr(pos + 1, line_sz)
		     << endl; 
		pos = permute(line);
	}
	return 0;
}
