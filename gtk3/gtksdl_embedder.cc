// embeds a SDL window inside a tab
// doesn't work :(
#include <iostream>
#include <fstream>
#include <string>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/label.h>
#include <gtkmm/socket.h>
#include <gtkmm/notebook.h>

using std::string;
using std::ifstream;
using Gtk::Application;
using Gtk::Window;
using Gtk::Label;
using Gtk::Socket;
using Gtk::Notebook;

class MainWindow : public Window {
protected:
	string title, tabTitle, idFileName;
	Notebook noteBook;
	Label tabLabel, placeHolder;
	Socket tabContent;
public:
	MainWindow()
	: title("SDL embedding test"), tabTitle("SDL client"),
	idFileName("appid.out") {
		set_title(title);
		tabLabel.set_text(tabTitle);
		set_default_size(400, 400);
		set_border_width(10);

		ifstream idFile(idFileName);
		if(idFile) {
			::Window sockID;
			idFile >> sockID;
			idFile.close();
			std::clog << sockID << '\n';
			tabContent.add_id(sockID);
			noteBook.append_page(tabContent, tabLabel);
		} else {
			placeHolder.set_text("Error loading SDL");
			noteBook.append_page(placeHolder, tabLabel);
		}
		add(noteBook);
		show_all_children();
	}
	virtual ~MainWindow() {}
};

int main(int argc, char *argv[]) {
	const string appID = "cpp_learn.gtk3.gtksdl";
	auto app = Application::create(argc, argv, appID);
	MainWindow mWin;
	return app->run(mWin);
}
