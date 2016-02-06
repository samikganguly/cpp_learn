#include <iostream>
#include <string>

int main(void) {
	std::cout << "What is your name?";
	std::string name;
	std::cin >> name;// if two names are entered separated with whitespace
	                 // the second word remains in cin buffer and 2nd cin 
	                 // reads it in name
	std::cout << "Hello, " << name << std::endl << "And what is yours? ";
	std::cin >> name;
	std::cout << "Hello, " << name << "; nice to meet you, too" << std::endl;
	return 0;
}
