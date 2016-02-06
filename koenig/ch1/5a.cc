#include <iostream>
#include <string>

int main(void) {
	{
		std::string s = "a string";
		{
			std::string x = s + ", really";
			std::cout << s << std::endl;
		}
		std::cout << x << std::endl;//not valid because x is out of scope
	}
	return 0;
}
