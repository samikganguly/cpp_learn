// passing arguments to thread function by reference
#include <iostream>
#include <thread>

int main(void) {
	int i = 101;
	std::thread t([&i]{
		for(int c = 0; c < 100000; c++) i += c;
	});
	t.join();
	std::cout << i << '\n';
	return 0;
}
