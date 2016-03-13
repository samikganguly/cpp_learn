// test the scale widget. It displays and takes its value from a textbox
#include <iostream>
#include <iomanip>
#include <string>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/scale.h>
#include <gtkmm/adjustment.h>

using std::string;
using std::fixed;
using std::stringstream;
using std::streamsize;
using std::stod;
using Gtk::Application;
using Gtk::Window;
using Gtk::Box;
using Gtk::Entry;
using Gtk::Scale;
using Gtk::Adjustment;

class MainWindow : public Window {
protected:
	double min, max;
	string title;
	Box layout;
	Scale scale;
	Entry scaleVal;
	string fixed_to_string(double val, streamsize precision) const {
		stringstream sstr;
		auto prec = sstr.precision(precision);
		sstr << fixed << val;
		sstr.precision(prec);
		return sstr.str();
	}
public:
	MainWindow()
	: title("Scale test"), min(0), max(100) {
		set_title(title);
		scaleVal.set_max_length(6);
		scaleVal.set_text(fixed_to_string(min, 2));
		
		scale.set_draw_value(false);
		scale.set_size_request(100, 12);
		
		auto scaleModel = scale.get_adjustment();
		scaleModel->set_lower(min);
		scaleModel->set_upper(max);
		scaleModel->set_step_increment(10);
		scaleModel->set_page_increment(20);
		scaleModel->set_value(min);
		// send value from the entry to scale
		scaleVal.signal_activate().connect(
		[this] {
			double val = 0;
			try {
				val = stod(scaleVal.get_text());
			} catch(...) {
				val = 0;
			}
			if(val > max) val = max;
			else if(val < min) val = min;
			scaleVal.set_text(fixed_to_string(val, 2));
			scale.get_adjustment()->set_value(val);
		});
		// send value from scale to entry
		scale.signal_value_changed().connect(
		[this] {
			double val = scale.get_adjustment()->get_value();
			scaleVal.set_text(fixed_to_string(val, 2));
		});
		layout.pack_start(scale);
		layout.pack_start(scaleVal);
		add(layout);
		show_all_children();
	}
	virtual ~MainWindow() {}
};

int main(int argc, char *argv[]) {
	const string appID = "cpp_learn.gtk3.scaletest";
	auto app = Application::create(argc, argv, appID);
	MainWindow mWin;
	return app->run(mWin);
}
