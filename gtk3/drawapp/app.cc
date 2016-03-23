#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include "app.h"

using Gtk::Builder;
using Gtk::Box;

MainWindow
::MainWindow()
: title{"Draw"} {
	add_action("drawapp.tool.line_seg", []{});
	add_action("drawapp.tool.curve", []{});
	add_action("drawapp.tool.rect", []{});
	add_action("drawapp.tool.circle", []{});

	auto builder = Builder::create_from_file("drawapp.glade");
	mainBox = nullptr;
	builder->get_widget<Box>("main_box", mainBox);

	set_title(title);
	add(*mainBox);
	show_all();
}

MainWindow
::~MainWindow() {
	delete mainBox;
}
