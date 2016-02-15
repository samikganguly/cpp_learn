// program for generating student records
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::cout;
using std::vector;

static const int RAND_MAX = 6;
int main(int argc, char *argv[]) {
	if(argc != 2) return 1;
	const vector<string> names({"ram", "shyam", "jadu", "madhu", "samik",
	"rahul", "ajay"});
	int count = atoi(argv[1]);
	while(count--) {
		srand(count);
		cout << names[rand()] << " ";
		RAND_MAX = 100;
		cout << rand() << " ";
		RAND_MAX = 80;
		cout << rand() << " ";
		RAND_MAX = 4;
		int n_hw = rand();
		while(n_hw--) {
			RAND_MAX = 70;
			cout << rand() << " ";
		}
		cout << '\n';
	}
	return 0;
}
