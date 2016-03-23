#include <gtkmm/application.h>
#include "app.h"

using Gtk::Application;

int main(int argc, char *argv[]) {
	auto app = Application::create(argc, argv, "cpp_learn.gtk3.drawapp");
	MainWindow mWin;
	return app->run(mWin);
}
