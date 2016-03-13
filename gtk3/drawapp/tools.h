// various tools for drawing
#include <vector>
#include <array>
#include <gdkmm/rectangle.h>
#include <gdkmm/rgba.h>
#include <gdkmm/types.h>
#include <cairomm/context.h>

#ifndef GUARD_TOOLS_H
#define GUARD_TOOLS_H

class DashType {
protected:
	double strokeWidth = 0.0;
	std::vector<double> dashes;
public:
	virtual bool operator!= (const DashType& anotherDash) noexcept;
	inline virtual const std::vector<double>& get_dashes() const noexcept {
		return dashes;
	}
	virtual double get_start_offset() const noexcept = 0;
	virtual ~DashType() {}
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
protected:
	Gdk::Point head, tail;
	Gdk::Rectangle bound;
	bool isStroke = true;
	double strokeWidth = 1;
	Gdk::RGBA strokeColor = DrawTool::black;
	DashType *dashType;

	static const Gdk::RGBA black, white;
public:
	virtual const Gdk::Rectangle& get_bound() const noexcept;
	virtual void draw_stroke(const bool draw) noexcept;
	virtual void set_stroke_width(const double strokeWidth) noexcept;
	virtual void set_stroke_color(const Gdk::RGBA& color) noexcept;
	virtual void set_dash_type(DashType *dashType) noexcept;
	virtual bool is_stroke() const noexcept;
	virtual double get_stroke_width() const noexcept;
	virtual const Gdk::RGBA& get_stroke_color() const noexcept;
	virtual DashType* get_dash_type() const noexcept;
	virtual const Gdk::Point& get_head() const noexcept;
	virtual const Gdk::Point& get_tail() const noexcept;
	virtual void draw(Cairo::Context&) const noexcept = 0;
	virtual ~DrawTool() {}
};

class LineSegTool : public DrawTool {
public:
	LineSegTool(const Gdk::Point& head, const Gdk::Point& tail) noexcept;
	LineSegTool(const std::array<Gdk::Point, 2>& points) noexcept;
	virtual void draw(Cairo::Context&) const noexcept override;
};

class BezierCurveSegTool : public DrawTool {
protected:
	Gdk::Point c1, c2;
public:
	BezierCurveSegTool(const Gdk::Point& head, const Gdk::Point& tail,
		const Gdk::Point& c1, const Gdk::Point& c2) noexcept;
	BezierCurveSegTool(const std::array<Gdk::Point, 4>& points) noexcept;
	virtual const Gdk::Point& get_head_control() const noexcept;
	virtual const Gdk::Point& get_tail_control() const noexcept;
	virtual void draw(Cairo::Context&) const noexcept override;
};

class ShapeDrawTool : public DrawTool {
protected:
	bool isFill = false;
	Gdk::RGBA fillColor = DrawTool::white;
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
public:
	CircleTool(const Gdk::Point& center, 
		const Gdk::Point& pointOnCircle) noexcept;
	virtual const Gdk::Point& get_center() const noexcept;
	virtual int get_radius() const noexcept;
	virtual void draw(Cairo::Context&) const noexcept override;
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
	virtual void draw(Cairo::Context&) const noexcept override;
};

#endif
