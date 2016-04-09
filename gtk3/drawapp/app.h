// main drawing application

#ifndef GUARD_APP_H
#define GUARD_APP_H

#include <vector>
#include <utility>
#include <memory>
#include <glibmm/refptr.h>
#include <glibmm/ustring.h>
#include <giomm/simpleaction.h>
#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/alignment.h>
#include <gtkmm/radiotoolbutton.h>
#include "tools.h"

enum class DrawToolType {
	none, line_seg, curve, rect, circle
};

class MainApplication : public Gtk::Application {
private:
	Glib::RefPtr<Gtk::Builder> ui;
	DrawToolType current_tool = DrawToolType::none;
	std::unique_ptr<DrawTool> current_shape;
	std::vector<std::unique_ptr<DrawTool>> shapes;
	std::vector<std::tuple<DrawToolType, Glib::RefPtr<Gio::SimpleAction>,
		Gtk::Box*, Gtk::RadioToolButton*>> tools;

	Gtk::ApplicationWindow* main_window;
	Gtk::Alignment* tool_prop_holder;
	DrawingArea *drawing_area;

	MainApplication(int& argc, char**& argv, const Glib::ustring& id);
protected:
	void on_startup() override;
	void on_activate() override;
public:
	static Glib::RefPtr<MainApplication> create(int& argc, char**& argv,
		const Glib::ustring& id);
};

#endif
