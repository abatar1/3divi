#define _USE_MATH_DEFINES
#include <cmath>
#include "Line.h"
#include "Triangle.h"

Line::Line(Point _start, Point _end) : start(_start), end(_end) {}

Line::Line() : start(Point()), end(Point()) {}

double Line::Length()
{
	return sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
}

void Line::RotateX()
{
	auto tmp = start;
	start = end;
	end = tmp;
}

void Line::RotateY()
{
	auto tmp = start;
	start = Point(end.y, end.x);
	end = Point(tmp.y, tmp.x);
}

double Line::AngleWith(Line other)
{
	auto AB = end - start;
	auto BC = other.end - other.start;
	return acos(abs(AB.x*BC.x + AB.y*BC.y) / (sqrt(pow(AB.x, 2) + pow(AB.y, 2)) * sqrt(pow(BC.x, 2) + pow(BC.y, 2)))) * 180.0 / M_PI;
}

Point Line::IntersectionWith(Line other)
{
	auto s1 = end - start;
	auto s2 = other.end - other.start;
	auto t = (s2.x * (start.y - other.start.y) - s2.y * (start.x - other.start.x)) / (-s2.x * s1.y + s1.x * s2.y);

	return Point(start.x + t * s1.x, start.y + t * s1.y);
}

bool Line::operator==(Line& a)
{
	return a.end == end && a.start == start;
}

bool Line::operator<(Line& a)
{
	return Length() < a.Length();
}
