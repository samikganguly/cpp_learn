#include <iostream>
#include <string>

int main(void) {
	{
		std::string s = "a string";
		{
			std::string x = s + ", really";
			std::cout << s << std::endl;
			std::cout << x << std::endl;
		}
	}
	return 0;
}
