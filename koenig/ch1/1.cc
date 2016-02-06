#include <string>

int main(void) {
	const std::string hello = "Hello";
	const std::string message = hello + ", World" + "!";
	// valid as string object has overload for left-associative + operator
	// which returns another string object concatenating the operands
	// so hello + ", World" + "!" is equivalent to (hello + ", World") + "!"
	// or string tmp = hello + ", World"; tmp + "!";
	return 0;
}
