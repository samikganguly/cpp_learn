#include "app.h"

int main(int argc, char** argv) {
	auto app = MainApplication::create(argc, argv, "cpp_learn.gtk3.drawapp");
	return app->run();
}
