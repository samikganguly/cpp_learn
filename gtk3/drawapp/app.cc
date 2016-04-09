#include <vector>
#include <utility>
#include <glibmm/refptr.h>
#include <glibmm/ustring.h>
#include <glibmm/variant.h>
#include <giomm/simpleaction.h>
#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/alignment.h>
#include <gtkmm/radiotoolbutton.h>
#include <gtkmm/drawingarea.h>
#include <gdk/gdk.h>
#include <gdkmm/types.h>
#include "app.h"

using std::size_t;
using std::vector;
using std::tuple;
using std::make_tuple;
using std::get;
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
using Gtk::RadioToolButton;
using Gtk::DrawingArea;
using Gdk::Point;

MainApplication
::MainApplication(int& argc, char**& argv, const ustring& id)
: Application(argc, argv, id) {}

void MainApplication::on_startup() {
	Gtk::Box *line_prop_box, *curve_prop_box, *rect_prop_box,
		*circle_prop_box;
	Gtk::RadioToolButton *line_tool_btn, *curve_tool_btn, *rect_tool_btn,
		*circle_tool_btn;

	Application::on_startup();

	ui = Builder::create_from_file("drawapp.glade");

	ui->get_widget<Alignment>("tool_property_frame_align", tool_prop_holder);
	ui->get_widget<Box>("line_seg_tool_prop_box", line_prop_box);
	ui->get_widget<RadioToolButton>("line_seg_tool_btn", line_tool_btn);
	ui->get_widget<Box>("curve_tool_prop_box", curve_prop_box);
	ui->get_widget<RadioToolButton>("curve_tool_btn", curve_tool_btn);
	ui->get_widget<Box>("rect_tool_prop_box", rect_prop_box);
	ui->get_widget<RadioToolButton>("rect_tool_btn", rect_tool_btn);
	ui->get_widget<Box>("circle_tool_prop_box", circle_prop_box);
	ui->get_widget<RadioToolButton>("circle_tool_btn", circle_tool_btn);

	tools.push_back(
		make_tuple(
			DrawToolType::line_seg,
			SimpleAction::create_bool("line_seg", true),
			line_prop_box,
			line_tool_btn
		)
	);
	tools.push_back(
		make_tuple(
			DrawToolType::curve,
			SimpleAction::create_bool("curve", false),
			curve_prop_box,
			curve_tool_btn
		)
	);
	tools.push_back(
		make_tuple(
			DrawToolType::rect,
			SimpleAction::create_bool("rect", false),
			rect_prop_box,
			rect_tool_btn
		)
	);
	tools.push_back(
		make_tuple(
			DrawToolType::circle,
			SimpleAction::create_bool("circle", false),
			circle_prop_box,
			circle_tool_btn
		)
	);
}

void MainApplication::on_activate() {
	ui->get_widget<ApplicationWindow>("main_window", main_window);
	ui->get_widget<DrawingArea>("draw_area", drawing_area);

	cctx = drawing_area->get_window()->create_cairo_context();
	drawing_area->add_events(KEY_PRESS_MASK | BUTTON_PRESS_MASK);
	drawing_area->signal_button_press_event().connect(
	[this, drawing_area] (GdkEventButton *evt)=>bool {
		if(current_tool != DrawToolType::none && evt->button == 1) {
			if(current_shape == nullptr) {
				switch(current_tool) {
				case DrawToolType::line_seg:
					current_shape = unique_ptr<DrawTool>
						(new LineSegTool);
					break;
				case DrawToolType::curve:
					current_shape = unique_ptr<DrawTool>
						(new BezierCurveSegTool);
					break;
				case DrawToolType::rect:
					current_shape = unique_ptr<DrawTool>
						(new RectTool);
					break;
				case DrawToolType::circle:
					current_shape = unique_ptr<DrawTool>
						(new CircleTool);
				}
			}
			if(current_shape->has_next_state())
				current_shape->next_state(
					Point((int)(evt->x),(int)(evt->y)));	
			else {
				shapes.push_back(current_shape);
				current_shape = nullptr;
			}
			drawing_area->queue_draw();
		}
		return true;
	});
	drawing_area->signal_key_press_event().connect(
	[this, drawing_area] (GdkEventKey *evt)=>bool{
		if(evt->keyval == GDK_KEY_ESCAPE &&
		current_tool != DrawToolType::none && 
		current_shape != nullptr) {
			current_shape = nullptr;
		}
		return true;
	});
	drawing_area->signal_draw().connect();

	for(auto tool : tools) {
		get<1>(tool)->signal_change_state().connect(
		[this, tool] (const VariantBase& vb) {
			current_tool = get<0>(tool);
			if(get<3>(tool)->get_active()) {
				if(tool_prop_holder->get_child() != nullptr)
					tool_prop_holder->remove();
				tool_prop_holder->add(*get<2>(tool));
			} else {
				if(tool_prop_holder->get_child() != nullptr)
					tool_prop_holder->remove();
			}
		});
		main_window->add_action(get<1>(tool));
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
