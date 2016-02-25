#include <iostream>
#include <thread>

int main(void) {
	std::thread t([]{
		std::cout << "Hello world! from thread\n";
	});
	std::cout << "Hello world! from main\n";
	t.join();
	return 0;
}
