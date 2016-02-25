// out of scope access from thread to a local variable
#include <iostream>
#include <thread>

class func {
private:
	int& i;
public:
	func(int& member):i(member) {}
	void operator ()() const {
		for(int c = 0; c < 1000000; c++) {
			i += c;
		}
	}
};

int main(void) {
	int test = 10;
	func f(test);
	std::thread t(f);
	/*
	t.detach();// main thread doesn't wait for thread t to complete,
	           // main's local variable test is accessed from t via f
	*/
	t.join();
	std::cout << test << '\n';
	return 0;
}
