// main drawing application

#ifndef GUARD_APP_H
#define GUARD_APP_H

#include <vector>
#include <glibmm/refptr.h>
#include <glibmm/ustring.h>
#include <giomm/simpleaction.h>
#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/alignment.h>
#include <gtkmm/toggletoolbutton.h>

class MainApplication : public Gtk::Application {
private:
	Glib::RefPtr<Gtk::Builder> ui;
	std::vector<Glib::RefPtr<Gio::SimpleAction>> toolbar_actions;

	Gtk::ApplicationWindow* main_window;
	Gtk::Alignment* tool_prop_holder;
	Gtk::Box* line_prop_box, *curve_prop_box, *rect_prop_box,
	          *circle_prop_box;
	Gtk::ToggleToolButton* line_tool_btn, *curve_tool_btn, *rect_tool_btn,
	                       *circle_tool_btn;

	MainApplication(int& argc, char**& argv, const Glib::ustring& id);
protected:
	void on_startup() override;
	void on_activate() override;
public:
	static Glib::RefPtr<MainApplication> create(int& argc, char**& argv,
		const Glib::ustring& id);
};

#endif
