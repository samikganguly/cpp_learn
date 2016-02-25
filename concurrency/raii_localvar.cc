// ensuring thread join with RAII
#include <iostream>
#include <thread>

class func {
private:
	int& i;
public:
	func(int& member) : i(member) {}
	void operator() () {
		for(int c = 0; c < 100000; c++) i+= c;
		std::cout << i << '\n';
	}
};

class thread_guard {
private:
	std::thread t;
public:
	// std::move() is required as copy assinment operation is deleted in
	// std::thread class
	explicit thread_guard(std::thread raw) : t(std::move(raw)) {}
	thread_guard(thread_guard&) = delete;
	thread_guard& operator= (thread_guard&) = delete;
	~thread_guard() { // before guard object is destroyed,
		          // it waits for the thread to complete
		if(t.joinable()) t.join();
	}
};

int main(void) {
	int test = 10;
	thread_guard gt(std::thread(func{test}));
	// why the following code doesn't write anything to terminal?
	// because instead of initializing a temporary 'func' object
	// with 'test', it calls func(test) and passes void to std::thread()
	// constructor, initializer list is used to prevent it
	// thread_guard gt(std::thread(func(test)));

	// the following two operations are prohibited by deleted function
	// thread_guard gt1(gt);
	// gt = gt1;
	return 0;
}
