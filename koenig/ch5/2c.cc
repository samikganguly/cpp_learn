// program for generating student records
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::cout;
using std::vector;

int main(int argc, char *argv[]) {
	if(argc != 2) return 1;
	const vector<string> names({"ram", "shyam", "jadu", "madhu", "samik",
	"rahul", "ajay"});
	int count = atoi(argv[1]);
	while(count--) {
		srand(count);
		cout << names[rand() % 7] << " ";
		cout << rand() % 101 << " ";
		cout << rand() % 81 << " ";
		int n_hw = rand() % 5;
		while(n_hw--) {
			cout << rand() % 71 << " ";
		}
		cout << '\n';
	}
	return 0;
}
