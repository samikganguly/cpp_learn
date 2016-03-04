// test for a signal handler with lambda function
#include <string>
#include <gtkmm.h>

using std::string;

class TestWindow : public Gtk::Window {
protected:
	string title, btnDefaultLabel, btnClickedLabel;
	Gtk::Button button;
public:
	TestWindow()
	: btnDefaultLabel("_Click Me!"), btnClickedLabel("_Clicked!"),
	button(btnDefaultLabel, true), title("Click on The Button") {
		set_title(title);
		button.signal_clicked().connect(
		[this] {
			auto btnLabel = button.get_label();
			if(btnLabel == btnDefaultLabel)
				button.set_label(btnClickedLabel);
			else
				button.set_label(btnDefaultLabel);
		});
		add(button);
		show_all_children();
	}
	virtual ~TestWindow() {}
};

int main(int argc, char *argv[]) {
	const string appID = "org.gtkmm.example.signal-test";
	constexpr int w = 200, h = 200;
	auto app = Gtk::Application::create(argc, argv, appID);
	TestWindow mainWindow;
	mainWindow.set_default_size(w, h);
	return app->run(mainWindow);
}
