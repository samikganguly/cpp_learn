// Test a toggle button
#include <string>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/togglebutton.h>

using std::string;
using Gtk::Application;
using Gtk::Window;
using Gtk::ToggleButton;

class MainWindow : public Window {
protected:
	string defaultLabel, clickedLabel, title;
	ToggleButton tBtn;
public:
	MainWindow()
	: defaultLabel("_Click Me!"), clickedLabel("_Clicked!"),
	title("ToggleButton Test"), tBtn(defaultLabel, true) {
		set_title(title);
		tBtn.signal_clicked().connect(
		[this] {
			if(tBtn.get_active())
				tBtn.set_label(clickedLabel);
			else
				tBtn.set_label(defaultLabel);
		});
		add(tBtn);
		tBtn.show();
	}
	virtual ~MainWindow() {}
};

int main(int argc, char *argv[]) {
	const string appID = "cpp_learn.gtk3.togglebtn";
	constexpr int w = 200, h = 200;
	auto app = Application::create(argc, argv, appID);
	MainWindow mWin;
	mWin.set_default_size(w, h);
	return app->run(mWin);
}
