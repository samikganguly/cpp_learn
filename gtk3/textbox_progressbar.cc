// text entry with progressbar
#include <string>
#include <stdexcept>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>

using std::string;
using std::to_string;
using std::stoi;
using Gtk::Application;
using Gtk::Window;
using Gtk::Box;
using Gtk::ORIENTATION_VERTICAL; 
using Gtk::Label;
using Gtk::Entry;

class MainWindow : public Window {
protected:
	int min, max;
	string title;
	Box layout;
	Label label;
	Entry entry, anotherEntry;
	void show_progress() {
		int input;
		try {
			input = stoi(entry.get_text());
			if(input < min) input = min;
			if(input > max) input = max;
		} catch(...) {
			input = 0;
		}
		entry.set_text(to_string(input));
		const double frac = (double)input / (double)(max - min);
		entry.set_progress_fraction(frac);
	}
public:
	MainWindow()
	: min(0), max(100), title("Text entry with progressbar"),
	label("Enter a number between 0 and 100:"),
	layout(ORIENTATION_VERTICAL) {
		set_title(title);
		entry.set_text(to_string(min));
		entry.signal_activate().connect(
		[this] {
			show_progress();
		});
		entry.signal_focus_out_event().connect(
		[this](GdkEventFocus *evt)->bool {
			show_progress();
			return true;
		});
		layout.set_border_width(10);
		layout.pack_start(label);
		layout.pack_start(entry);
		layout.pack_start(anotherEntry);
		add(layout);
		show_all_children();
	}
	virtual ~MainWindow() {}
};

int main(int argc, char *argv[]) {
	const string appID = "cpp_learn.gtk3.entrytest";
	auto app = Application::create(argc, argv, appID);
	MainWindow mWin;
	return app->run(mWin);
}
