#include <string>

int main(void) {
	const std::string exclam = "!";
	const std::string message = "Hello" + ", world" + exclam;
	// not valid as string literal doesn't have a overload for + operator
	return 0;
}
