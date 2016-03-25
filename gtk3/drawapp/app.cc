#include <vector>
#include <glibmm/refptr.h>
#include <glibmm/ustring.h>
#include <glibmm/variant.h>
#include <giomm/simpleaction.h>
#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/alignment.h>
#include <gtkmm/toggletoolbutton.h>
#include "app.h"

using std::size_t;
using std::vector;
using Glib::RefPtr;
using Glib::ustring;
using Glib::VariantBase;
using Glib::Variant;
using Gtk::Builder;
using Gio::SimpleAction;
using Gtk::Application;
using Gtk::ApplicationWindow;
using Gtk::Box;
using Gtk::Alignment;
using Gtk::ToggleToolButton;

MainApplication
::MainApplication(int& argc, char**& argv, const ustring& id)
: Application(argc, argv, id) {}

void MainApplication::on_startup() {
	Application::on_startup();

	ui = Builder::create_from_file("drawapp.glade");

	toolbar_actions.push_back(SimpleAction::create_bool("line_seg", false));
	toolbar_actions.push_back(SimpleAction::create_bool("curve", false));
	toolbar_actions.push_back(SimpleAction::create_bool("rect", false));
	toolbar_actions.push_back(SimpleAction::create_bool("circle", false));

	ui->get_widget<Alignment>("tool_property_frame_align", tool_prop_holder);
	ui->get_widget<Box>("line_seg_tool_prop_box", line_prop_box);
	ui->get_widget<ToggleToolButton>("line_seg_tool_btn", line_tool_btn);
	ui->get_widget<Box>("curve_tool_prop_box", curve_prop_box);
	ui->get_widget<ToggleToolButton>("curve_tool_btn", curve_tool_btn);
	ui->get_widget<Box>("rect_tool_prop_box", rect_prop_box);
	ui->get_widget<ToggleToolButton>("rect_tool_btn", rect_tool_btn);
	ui->get_widget<Box>("circle_tool_prop_box", circle_prop_box);
	ui->get_widget<ToggleToolButton>("circle_tool_btn", circle_tool_btn);

	toolbar_actions[0]->signal_change_state().connect(
	[this] (const VariantBase& vb) {
		if(line_tool_btn->get_active()) {
			if(tool_prop_holder->get_child() != nullptr)
				tool_prop_holder->remove();
			tool_prop_holder->add(*line_prop_box);
		} else {
			if(tool_prop_holder->get_child() != nullptr)
				tool_prop_holder->remove();
		}
	});
	toolbar_actions[1]->signal_change_state().connect(
	[this] (const VariantBase& vb) {
		if(curve_tool_btn->get_active()) {
			if(tool_prop_holder->get_child() != nullptr)
				tool_prop_holder->remove();
			tool_prop_holder->add(*curve_prop_box);
		} else {
			if(tool_prop_holder->get_child() != nullptr)
				tool_prop_holder->remove();
		}
	});
	toolbar_actions[2]->signal_change_state().connect(
	[this] (const VariantBase& vb) {
		if(rect_tool_btn->get_active()) {
			if(tool_prop_holder->get_child() != nullptr)
				tool_prop_holder->remove();
			tool_prop_holder->add(*rect_prop_box);
		} else {
			if(tool_prop_holder->get_child() != nullptr)
				tool_prop_holder->remove();
		}
	});
	toolbar_actions[3]->signal_change_state().connect(
	[this] (const VariantBase& vb) {
		if(circle_tool_btn->get_active()) {
			if(tool_prop_holder->get_child() != nullptr)
				tool_prop_holder->remove();
			tool_prop_holder->add(*circle_prop_box);
		} else {
			if(tool_prop_holder->get_child() != nullptr)
				tool_prop_holder->remove();
		}
	});
}

void MainApplication::on_activate() {
	ui->get_widget<ApplicationWindow>("main_window", main_window);
	for(RefPtr<SimpleAction> tool_action : toolbar_actions) {
		main_window->add_action(tool_action);
	}
	main_window->signal_hide().connect(
	[this] {
		delete main_window;
	});
	add_window(*main_window);
	main_window->show_all();
}

RefPtr<MainApplication> MainApplication::create(int& argc, char**& argv,
	const Glib::ustring& id) {
	return RefPtr<MainApplication>(new MainApplication(argc, argv, id));
}
