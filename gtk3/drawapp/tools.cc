#include "tools.h"
#include <utility>
#include <algorithm>
#include <cmath>

using std::abs;
using std::sqrt;
using std::vector;
using std::array;
using std::pair;
using std::min;
using std::minmax;
using Gdk::Rectangle;
using Gdk::RGBA;
using Gdk::Point;
using Cctx = Cairo::Context;

bool DashType::operator!= (const DashType& d1) noexcept {
	return strokeWidth != d1.strokeWidth;
}

FineDot::FineDot(const double sw) noexcept {
	strokeWidth = sw;
	dashes.insert(dashes.begin(), {sw, sw});
}

double FineDot::get_start_offset() const noexcept {
	return strokeWidth;
}

FineDash::FineDash(const double sw) noexcept {
	strokeWidth = sw;
	dashes.insert(dashes.begin(), {sw * 2, sw});
}

double FineDash::get_start_offset() const noexcept {
	return strokeWidth;
}

Dot::Dot(const double sw) noexcept {
	strokeWidth = sw;
	dashes.insert(dashes.begin(), {sw, sw * 2});
}

double Dot::get_start_offset() const noexcept {
	return strokeWidth * 2;
}

Dash::Dash(const double sw) noexcept {
	strokeWidth = sw;
	dashes.insert(dashes.begin(), {sw * 4, sw * 2});
}

double Dash::get_start_offset() const noexcept {
	return strokeWidth * 2;
}

const RGBA DrawTool::black{"black"}, DrawTool::white{"white"};

void DrawTool::set_dash_type(DashType *dt) noexcept {
	dashType = dt;
}

void DrawTool::draw_stroke(const bool draw = true) noexcept {
	isStroke = draw;
}

void DrawTool::set_stroke_width(const double sw) noexcept {
	strokeWidth = sw;
}

void DrawTool::set_stroke_color(const RGBA& color) noexcept {
	strokeColor = color;
}

const Rectangle& DrawTool::get_bound() const noexcept {
	return bound;
}

bool DrawTool::is_stroke() const noexcept {
	return isStroke;
}

double DrawTool::get_stroke_width() const noexcept {
	return strokeWidth;
}

const RGBA& DrawTool::get_stroke_color() const noexcept {
	return strokeColor;
}

DashType* DrawTool::get_dash_type() const noexcept {
	return dashType;
}

const Point& DrawTool::get_head() const noexcept {
	return head;
}

const Point& DrawTool::get_tail() const noexcept {
	return tail;
}

LineSegTool
::LineSegTool(const Point& h, const Point& t) noexcept {
	head = std::move(h);
	tail = std::move(t);
	const int hx = h.get_x(), hy = h.get_y(),
		tx = t.get_x(), ty = t.get_y();
	bound.set_x(min(hx, tx));
	bound.set_y(min(hy, ty));
	bound.set_width(abs(hx - tx));
	bound.set_height(abs(hy - ty));
}

LineSegTool
::LineSegTool(const array<Point, 2>& points) noexcept
: LineSegTool{points[0], points[1]} {}

void LineSegTool::draw(Cctx& ctx) const noexcept {
	ctx.set_source_rgba(strokeColor.get_red(), strokeColor.get_green(), 
		strokeColor.get_blue(), strokeColor.get_alpha());
	if(dashType != nullptr)
		ctx.set_dash(dashType->get_dashes(), 
			dashType->get_start_offset());
	ctx.begin_new_path();
	ctx.move_to(head.get_x(), head.get_y());
	ctx.line_to(tail.get_x(), tail.get_y());
	ctx.stroke();
}

BezierCurveSegTool
::BezierCurveSegTool(const Point& h, const Point& t, 
const Point& ctrl1, const Point& ctrl2) noexcept
: c1{ctrl1}, c2{ctrl2} {
	head = std::move(h);
	tail = std::move(t);
	const int hx = h.get_x(), hy = h.get_y(), tx = t.get_x(),
		ty = t.get_y(), c1x = c1.get_x(), c1y = c1.get_y(),
		c2x = c2.get_x(), c2y = c2.get_y();
	auto leftRight = minmax({hx, tx, c1x, c2x}),
		topBottom = minmax({hy, ty, c1y, c2y});
	bound.set_x(leftRight.first);
	bound.set_y(topBottom.first);
	bound.set_width(leftRight.second - leftRight.first);
	bound.set_height(topBottom.second - topBottom.first);
}

BezierCurveSegTool
::BezierCurveSegTool(const array<Point, 4>& points) noexcept
: BezierCurveSegTool{points[0], points[1], points[2], points[3]} {}

const Point& BezierCurveSegTool::get_head_control() const noexcept {
	return c1;
}

const Point& BezierCurveSegTool::get_tail_control() const noexcept {
	return c2;
}

void BezierCurveSegTool::draw(Cctx& ctx) const noexcept {
	ctx.set_source_rgba(strokeColor.get_red(), strokeColor.get_green(), 
		strokeColor.get_blue(), strokeColor.get_alpha());
	if(dashType != nullptr)
		ctx.set_dash(dashType->get_dashes(), 
			dashType->get_start_offset());
	ctx.begin_new_path();
	ctx.move_to(head.get_x(), head.get_y());
	ctx.curve_to(c1.get_x(), c1.get_y(), 
		c2.get_x(), c2.get_y(),
		tail.get_x(), tail.get_y());
	ctx.stroke();
}

void ShapeDrawTool::draw_fill(const bool draw = true) noexcept {
	isFill = draw;
}

void ShapeDrawTool::set_fill_color(const RGBA& color) noexcept {
	fillColor = color;
}

bool ShapeDrawTool::is_fill() const noexcept {
	return isFill;
}

const RGBA& ShapeDrawTool::get_fill_color() const noexcept {
	return fillColor;
}

double CircleTool::get_radius_from_pts(const Point& p1, 
	const Point& p2) noexcept {
	const int w = abs(p1.get_x() - p2.get_x()),
		h = abs(p1.get_y() - p2.get_y());
	return sqrt(w * w + h * h);
}

CircleTool
::CircleTool(const Point& c, const Point& t) noexcept {
	head = std::move(c);
	tail = std::move(t);
	const int radius = static_cast<int>
		(CircleTool::get_radius_from_pts(c, t));
	bound.set_x(c.get_x() - radius);
	bound.set_y(c.get_y() - radius);
	bound.set_width(radius * 2);
	bound.set_height(radius * 2);
}

const Point& CircleTool::get_center() const noexcept {
	return head;
}

int CircleTool::get_radius() const noexcept {
	return bound.get_x() - head.get_x();
}

void CircleTool::draw(Cctx& ctx) const noexcept {
	ctx.set_source_rgba(strokeColor.get_red(), strokeColor.get_green(), 
		strokeColor.get_blue(), strokeColor.get_alpha());
	if(dashType != nullptr)
		ctx.set_dash(dashType->get_dashes(), 
			dashType->get_start_offset());
	ctx.begin_new_path();
	ctx.arc(head.get_x(), head.get_y(),
		get_radius(), 0, 44 / 7);
	if(isFill) {
		ctx.stroke_preserve();
		ctx.set_source_rgba(fillColor.get_red(),
			fillColor.get_green(), fillColor.get_blue(),
			fillColor.get_alpha());
		ctx.fill();
	} else {
		ctx.stroke();
	}
}

RectTool
::RectTool(const Point& tl, const Point& br, const bool sq = false) noexcept
: isSquare(sq) {
	auto htx = minmax(tl.get_x(), br.get_x()),
		hty = minmax(tl.get_y(), br.get_y());
	head.set_x(htx.first);
	head.set_y(hty.first);
	if(sq) {
		const int wh = min(abs(br.get_x() - tl.get_x()),
			abs(br.get_y() - tl.get_y()));
		tail.set_x(head.get_x() + wh);
		tail.set_y(head.get_y() + wh);
	} else {
		tail.set_x(htx.second);
		tail.set_y(hty.second);
	}
	bound.set_x(head.get_x());
	bound.set_y(head.get_y());
	bound.set_width(tail.get_x() - head.get_x());
	bound.set_height(tail.get_y() - head.get_y());
}

void RectTool::set_square(const bool sq = true) noexcept {
	isSquare = sq;
}

bool RectTool::is_square() const noexcept {
	return isSquare;
}

void RectTool::draw(Cctx& ctx) const noexcept {
	ctx.set_source_rgba(strokeColor.get_red(), strokeColor.get_green(), 
		strokeColor.get_blue(), strokeColor.get_alpha());
	if(dashType != nullptr)
		ctx.set_dash(dashType->get_dashes(), 
			dashType->get_start_offset());
	ctx.begin_new_path();
	ctx.move_to(head.get_x(), head.get_y());
	ctx.line_to(tail.get_x(), head.get_y());
	ctx.line_to(tail.get_x(), tail.get_y());
	ctx.line_to(head.get_x(), tail.get_y());
	ctx.close_path();
	if(isFill) {
		ctx.stroke_preserve();
		ctx.set_source_rgba(fillColor.get_red(),
			fillColor.get_green(), fillColor.get_blue(),
			fillColor.get_alpha());
		ctx.fill();
	} else {
		ctx.stroke();
	}	
}
