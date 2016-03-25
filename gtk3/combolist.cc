// takes items from a combobox and adds it to a treeview list
#include <iostream>
#include <string>
#include <list>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/combobox.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treemodelcolumn.h>
#include <glibmm/refptr.h>

using std::string;
using std::list;
using Gtk::Application;
using Gtk::Window;
using Gtk::Box;
using Gtk::ORIENTATION_VERTICAL;
using Gtk::ComboBox;
using Gtk::Button;
using Gtk::ListStore;
using Gtk::TreeModel;
using Gtk::TreeView;
using Gtk::TreeModelColumn;
using Gtk::TreeModelColumnRecord;
using Glib::RefPtr;

class OptionRecord : public TreeModelColumnRecord {
public:
	TreeModelColumn<string> options;
	OptionRecord() { add(options); }
	virtual ~OptionRecord() {}
};

class MainWindow : public Window {
protected:
	string title;
	list<string> optionList;
	Box main, sub;
	ComboBox options;
	Button addOption;
	TreeView addedOptions;
	RefPtr<ListStore> optionStore, addedStore;
	OptionRecord optionRecord;
public:
	MainWindow()
	: title{"Combobox and Listbox test"},
	  optionList{"Ram", "Shyam", "Jadu", "Madhu"},
	  sub{ORIENTATION_VERTICAL},
	  addOption{"_Add to list", true} {
	  	optionStore = ListStore::create(optionRecord);
		options.set_model(optionStore);
		bool isFirstOption = true;
		for(auto i = optionList.begin(); i != optionList.end();) {
			auto optionRow = *(optionStore->append());
			optionRow[optionRecord.options] = *i;
			if(isFirstOption) {
				options.set_active(optionRow);
				isFirstOption = false;
			}
			i = optionList.erase(i);
		}
		// don't forget to add view column with pack_start()
		// or model won't be rendered in ComboBox
		options.pack_start(optionRecord.options);
		
	  	addedStore = ListStore::create(optionRecord);
		addedOptions.set_model(addedStore);
		// don't forget to add view column width append_column()
		// or model won't be rendered in TreeView
		addedOptions.append_column("Added options",
			optionRecord.options); 
		addOption.signal_clicked().connect(
		[this]{
			auto selectedIter = options.get_active();
			if(selectedIter != nullptr) {
				auto selectedRow = *selectedIter;
				string selected = selectedRow[
					optionRecord.options];
				auto addedIter = addedStore->append();
				auto addedRow = *addedIter;
				addedRow[optionRecord.options] = selected;
			}
		});

		sub.set_spacing(10);
		sub.pack_start(options);
		sub.pack_start(addOption);
		main.set_spacing(10);
		main.pack_start(sub);
		main.pack_start(addedOptions);

		set_title(title);
		set_default_size(500, 200);
		set_border_width(5);
		add(main);
		show_all_children();
	}
	virtual ~MainWindow() {}
};

int main(int argc, char *argv[]) {
	auto app = Application::create(argc, argv, "cpp_learn.gtk3.combolist");
	MainWindow mWin;
	return app->run(mWin);
}
