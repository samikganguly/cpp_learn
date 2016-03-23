// application interface handler
#ifndef GUARD_APP_H
#define GUARD_APP_H

#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/switch.h>
#include <gtkmm/colorbutton.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/combobox.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/toggletoolbutton.h>
#include <gtkmm/alignment.h>

class MainWindow : public Gtk::ApplicationWindow {
protected:
	std::string title;
	Gtk::Box *mainBox, *lineProperty, *curveProperty,
	         *rectProperty, *circleProperty;
	Gtk::Label *lineHead, *lineTail, *curveHead, *curveTail,
	           *curveCtrl1, *curveCtrl2, *rectPivot, *rectWidth,
	           *rectHeight, *circleCenter, *circleRadius;
	Gtk::CheckButton *showCurveCtrl, *showCircleCenter;
	Gtk::Switch *drawStroke, *drawBound, *fillShape;
	Gtk::ColorButton *strokeColor, *fillColor;
	Gtk::Alignment *toolPropBox;
public:
	MainWindow();
	virtual ~MainWindow();
};

#endif
