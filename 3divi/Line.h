#pragma once
#include "Point.h"

class Line
{
public:
	Point start;
	Point end;

	Line(Point _start, Point _end);

	double Length();
	void RotateX();
	void RotateY();
};