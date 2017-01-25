#include <cmath>
#include "Line.h"

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

bool Line::operator==(Line& a)
{
	return a.end == end && a.start == start;
}

bool Line::operator<(Line& a)
{
	return Length() < a.Length();
}
