#include <cmath>
#include "Line.h"

Line::Line(Point _start, Point _end) : start(_start), end(_end) {}

double Line::Length()
{
	return sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
}

void Line::RotateX()
{
	Point tmp = start;
	start = end;
	end = tmp;
}

void Line::RotateY()
{
	Point tmp = start;
	start = Point(end.y, end.x);
	end = Point(tmp.y, tmp.x);
}