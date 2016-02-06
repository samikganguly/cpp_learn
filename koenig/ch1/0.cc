//Decorated Greetings
#include <iostream>
#include <string>

int main(void) {
	std::string name;
	std::cout << "Please enter your name: ";
	std::cin >> name;
	const std::string greeting = "Hello, " + name + "!";
	// why does const string allow non-const variable in the initializer?
	// because const only protects against subsequent changes but allows 
	// initializers immediately after declaration and an initializer can 
	// contain previously arbitrary expressions, previously declared 
	// variables, function calls regardless of the variable's storage duration
	const std::string spaces(greeting.size(), ' ');
	const std::string first(greeting.size() + 2, '*');
	std::cout << first << std::endl;
	std::cout << "*" + spaces + "*" << std::endl;
	std::cout << "*" + greeting + "*" << std::endl;
	std::cout << "*" + spaces + "*" << std::endl;
	std::cout << first << std::endl;
	return 0;
}
