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

DashType DashType::emptyDash{true};

DashType& DashType::none() noexcept {
	return DashType::emptyDash;
}

DashType
::DashType(bool e) noexcept
: empty{e} {}

FineDot
::FineDot(const double sw) noexcept
: DashType{false} {
	strokeWidth = sw;
	dashes.insert(dashes.begin(), {sw, sw});
}

double FineDot::get_start_offset() const noexcept {
	return strokeWidth;
}

FineDash
::FineDash(const double sw) noexcept
: DashType{false} {
	strokeWidth = sw;
	dashes.insert(dashes.begin(), {sw * 2, sw});
}

double FineDash::get_start_offset() const noexcept {
	return strokeWidth;
}

Dot
::Dot(const double sw) noexcept
: DashType{false} {
	strokeWidth = sw;
	dashes.insert(dashes.begin(), {sw, sw * 2});
}

double Dot::get_start_offset() const noexcept {
	return strokeWidth * 2;
}

Dash
::Dash(const double sw) noexcept
: DashType{false} {
	strokeWidth = sw;
	dashes.insert(dashes.begin(), {sw * 4, sw * 2});
}

double Dash::get_start_offset() const noexcept {
	return strokeWidth * 2;
}

RGBA DrawTool::b{"black"}, DrawTool::w{"white"};

void DrawTool::draw_stroke(const bool draw = true) noexcept {
	isStroke = draw;
}

void DrawTool::set_stroke_width(const double sw) noexcept {
	strokeWidth = sw;
}

void DrawTool::set_stroke_color(const RGBA& color) noexcept {
	strokeColor = color;
}

void DrawTool::set_dash_type(DashType& dt) noexcept {
	dashType = dt;
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

const DashType& DrawTool::get_dash_type() const noexcept {
	return dashType;
}

const Point& DrawTool::get_head() const noexcept {
	return head;
}

const Point& DrawTool::get_tail() const noexcept {
	return tail;
}

void DrawTool::draw_bound(Cctx& ctx) const {
	ctx.set_source_rgba(
		DrawTool::black().get_red(),
		DrawTool::black().get_green(),
		DrawTool::black().get_blue(),
		DrawTool::black().get_alpha());
	ctx.set_line_width(0.5);
	ctx.begin_new_path();
	ctx.move_to(bound.get_x(), bound.get_y());
	ctx.line_to(bound.get_x() + bound.get_width(), bound.get_y());
	ctx.line_to(bound.get_x() + bound.get_width(), 
		bound.get_y() + bound.get_height());
	ctx.line_to(head.get_x(), tail.get_y() + bound.get_height());
	ctx.close_path();
	ctx.stroke();
}

RGBA& DrawTool::black() noexcept {
	return DrawTool::b;
}

RGBA& DrawTool::white() noexcept {
	return DrawTool::w;
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

void LineSegTool::draw(Cctx& ctx) const {
	ctx.set_source_rgba(strokeColor.get_red(), strokeColor.get_green(), 
		strokeColor.get_blue(), strokeColor.get_alpha());
	ctx.set_line_width(strokeWidth);
	if(!dashType.is_empty())
		ctx.set_dash(dashType.get_dashes(), 
			dashType.get_start_offset());
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

bool BezierCurveSegTool::is_control_points_shown() const noexcept {
	return showControls;
}

void BezierCurveSegTool::show_control_points(const bool show = true) noexcept {
	showControls = show;
}

void BezierCurveSegTool::draw(Cctx& ctx) const {
	ctx.set_source_rgba(strokeColor.get_red(), strokeColor.get_green(), 
		strokeColor.get_blue(), strokeColor.get_alpha());
	ctx.set_line_width(strokeWidth);
	if(!dashType.is_empty())
		ctx.set_dash(dashType.get_dashes(), 
			dashType.get_start_offset());
	ctx.begin_new_path();
	ctx.move_to(head.get_x(), head.get_y());
	ctx.curve_to(c1.get_x(), c1.get_y(), 
		c2.get_x(), c2.get_y(),
		tail.get_x(), tail.get_y());
	ctx.stroke();
	if(showControls) {
		ctx.set_source_rgba(
			DrawTool::black().get_red(),
			DrawTool::black().get_green(),
			DrawTool::black().get_blue(),
			DrawTool::black().get_alpha());
		ctx.set_line_width(0.5);
		DashType *dt = new FineDash(1);
		ctx.set_dash(dt->get_dashes(), dt->get_start_offset());
		delete dt;
		ctx.move_to(head.get_x(), head.get_y());
		ctx.line_to(c1.get_x(), c1.get_y());
		ctx.move_to(tail.get_x(), tail.get_y());
		ctx.line_to(c2.get_x(), c2.get_y());
		ctx.stroke();
		ctx.unset_dash();
		ctx.arc(c1.get_x(), c1.get_y(), 1, 0, 44 / 7);
		ctx.begin_new_sub_path();
		ctx.arc(c2.get_x(), c2.get_y(), 1, 0, 44 / 7);
		ctx.fill();
	}
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

bool CircleTool::is_center_shown() const noexcept {
	return showCenter;
}

void CircleTool::show_center(const bool show) noexcept {
	showCenter = show;
}

void CircleTool::draw(Cctx& ctx) const {
	ctx.set_source_rgba(strokeColor.get_red(), strokeColor.get_green(), 
		strokeColor.get_blue(), strokeColor.get_alpha());
	ctx.set_line_width(strokeWidth);
	if(!dashType.is_empty())
		ctx.set_dash(dashType.get_dashes(), 
			dashType.get_start_offset());
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
	if(showCenter) {
		ctx.set_source_rgba(DrawTool::black().get_red(),
			            DrawTool::black().get_green(),
			            DrawTool::black().get_blue(),
			            DrawTool::black().get_alpha());
		ctx.unset_dash();
		ctx.arc(head.get_x(), head.get_y(), 1, 0, 44 / 7);
		ctx.fill();
	}
}

RectTool
::RectTool(const Point& tl, const Point& br, const bool sq) noexcept
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

void RectTool::draw(Cctx& ctx) const {
	ctx.set_source_rgba(strokeColor.get_red(), strokeColor.get_green(), 
		strokeColor.get_blue(), strokeColor.get_alpha());
	ctx.set_line_width(strokeWidth);
	if(!dashType.is_empty())
		ctx.set_dash(dashType.get_dashes(), 
			dashType.get_start_offset());
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
