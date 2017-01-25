#pragma once
#include "Point.h"

class Line
{
public:
	Point start;
	Point end;

	Line(Point _start, Point _end);
	Line();

	double Length();
	void RotateX();
	void RotateY();

	bool operator==(Line& a);
	bool operator<(Line& a);
};