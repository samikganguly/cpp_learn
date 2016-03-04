#include <string>
#include <array>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/separator.h>

using std::string;
using std::to_string;
using std::array;
using Gtk::Application;
using Gtk::Window;
using Gtk::Button;
using Gtk::RadioButton;
using Gtk::Box;
using Gtk::ORIENTATION_VERTICAL;
using Gtk::ORIENTATION_HORIZONTAL;
using Gtk::Separator;

class MainWindow : public Window {
protected:
	string title, defaultLabel, activeLabel;
	Box outerBox, innerBox_top, innerBox_btm;
	array<RadioButton, 3> radios;
	Button closeBtn;
	Separator sep;
public:
	MainWindow()
	: title("RadioButton Test"), defaultLabel("radiobutton"),
	activeLabel("selected"), outerBox(ORIENTATION_VERTICAL),
	innerBox_top(ORIENTATION_HORIZONTAL),
	innerBox_btm(ORIENTATION_HORIZONTAL), closeBtn("_Close", true) {
		set_title(title);
		closeBtn.signal_clicked().connect(
		[this]{
			hide();
		});
		auto grp = radios[0].get_group();
		for(int i = 0; i < 3; ++i) {
			radios[i].set_label(defaultLabel + to_string(i));
			if(i != 0)
				radios[i].set_group(grp);
			radios[i].signal_clicked().connect(
			[this, i] {
				if(radios[i].get_active())
					radios[i].set_label(activeLabel
						+ to_string(i));
				else
					radios[i].set_label(defaultLabel
						+ to_string(i));
			});
		}
		radios[1].set_active();
		innerBox_top.set_border_width(10);
		for(int i = 0; i < 3; ++i) {
			innerBox_top.pack_start(radios[i]);
		}
		innerBox_btm.pack_start(closeBtn);
		outerBox.pack_start(innerBox_top);
		outerBox.pack_start(sep);
		outerBox.pack_start(innerBox_btm);
		set_border_width(10);
		add(outerBox);
		show_all_children();
	}
	virtual ~MainWindow() {}
};

int main(int argc, char *argv[]) {
	const string appID = "cpp_learn.gtk3.radiobuttontest";
	auto app = Application::create(argc, argv, appID);
	MainWindow mWin;
	return app->run(mWin);
}
