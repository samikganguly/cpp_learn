// various tools for drawing

#ifndef GUARD_TOOLS_H
#define GUARD_TOOLS_H

#include <vector>
#include <array>
#include <gdkmm/rectangle.h>
#include <gdkmm/rgba.h>
#include <gdkmm/types.h>
#include <cairomm/context.h>

class DashType {
private:
	static DashType emptyDash;
protected:
	bool empty = false;
	double strokeWidth = 0.0;
	std::vector<double> dashes;
	DashType(bool empty) noexcept;
public:
	inline const std::vector<double>& get_dashes() const noexcept {
		return dashes;
	}
	inline bool is_empty() const noexcept {
		return empty;
	}
	virtual double get_start_offset() const noexcept {}
	virtual ~DashType() {}
	static DashType& none() noexcept;
};

class FineDot : public DashType {
public:
	FineDot(const double strokeWidth) noexcept;
	virtual double get_start_offset() const noexcept override;
};

class FineDash : public DashType {
public:
	FineDash(const double strokeWidth) noexcept;
	virtual double get_start_offset() const noexcept override;
};

class Dot : public DashType {
public:
	Dot(const double strokeWidth) noexcept;
	virtual double get_start_offset() const noexcept override;
};

class Dash : public DashType {
public:
	Dash(const double strokeWidth) noexcept;
	virtual double get_start_offset() const noexcept override;
};

class DrawTool {
private:
	static Gdk::RGBA b, w;
protected:
	Gdk::Point head, tail;
	Gdk::Rectangle bound;
	bool isStroke = true;
	double strokeWidth = 1;
	Gdk::RGBA& strokeColor = DrawTool::black();
	DashType& dashType = DashType::none();
public:
	virtual const Gdk::Rectangle& get_bound() const noexcept;
	virtual void draw_stroke(const bool draw) noexcept;
	virtual void set_stroke_width(const double strokeWidth) noexcept;
	virtual void set_stroke_color(const Gdk::RGBA& color) noexcept;
	virtual void set_dash_type(DashType& dashType) noexcept;
	virtual bool is_stroke() const noexcept;
	virtual double get_stroke_width() const noexcept;
	virtual const Gdk::RGBA& get_stroke_color() const noexcept;
	virtual const DashType& get_dash_type() const noexcept;
	virtual const Gdk::Point& get_head() const noexcept;
	virtual const Gdk::Point& get_tail() const noexcept;
	virtual void draw(Cairo::Context&) const = 0;
	virtual void draw_bound(Cairo::Context&) const;
	virtual ~DrawTool() {}
	static Gdk::RGBA& black() noexcept;
	static Gdk::RGBA& white() noexcept;
};

class LineSegTool : public DrawTool {
public:
	LineSegTool(const Gdk::Point& head, const Gdk::Point& tail) noexcept;
	LineSegTool(const std::array<Gdk::Point, 2>& points) noexcept;
	virtual void draw(Cairo::Context&) const override;
};

class BezierCurveSegTool : public DrawTool {
protected:
	Gdk::Point c1, c2;
	bool showControls;
public:
	BezierCurveSegTool(const Gdk::Point& head, const Gdk::Point& tail,
		const Gdk::Point& c1, const Gdk::Point& c2) noexcept;
	BezierCurveSegTool(const std::array<Gdk::Point, 4>& points) noexcept;
	virtual const Gdk::Point& get_head_control() const noexcept;
	virtual const Gdk::Point& get_tail_control() const noexcept;
	virtual bool is_control_points_shown() const noexcept;
	virtual void show_control_points(const bool show) noexcept;
	virtual void draw(Cairo::Context&) const override;
};

class ShapeDrawTool : public DrawTool {
protected:
	bool isFill = false;
	Gdk::RGBA& fillColor = DrawTool::white();
public:
	virtual void draw_fill(const bool draw) noexcept;
	virtual void set_fill_color(const Gdk::RGBA& color) noexcept;
	virtual bool is_fill() const noexcept;
	virtual const Gdk::RGBA& get_fill_color() const noexcept;
	virtual ~ShapeDrawTool() {}
};

class CircleTool : public ShapeDrawTool {
private:
	static double get_radius_from_pts(const Gdk::Point& p1, 
		const Gdk::Point& p2) noexcept;
protected:
	bool showCenter;
public:
	CircleTool(const Gdk::Point& center, 
		const Gdk::Point& pointOnCircle) noexcept;
	virtual const Gdk::Point& get_center() const noexcept;
	virtual int get_radius() const noexcept;
	virtual bool is_center_shown() const noexcept;
	virtual void show_center(const bool show) noexcept;
	virtual void draw(Cairo::Context&) const override;
};

class RectTool : public ShapeDrawTool {
protected:
	bool isSquare;
public:
	RectTool(const Gdk::Point& topLeftCorner,
		const Gdk::Point& bottomRightCorner,
		const bool isSquare) noexcept;
	virtual void set_square(const bool isSquare) noexcept;
	virtual bool is_square() const noexcept;
	virtual void draw(Cairo::Context&) const override;
};

#endif
