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
	double FindAngle(Line other);
	Point FindIntersection(Line other);

	bool operator==(Line& a);
	bool operator<(Line& a);
};