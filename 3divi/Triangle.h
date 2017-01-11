#pragma once
#include "Point.h"
#include "Line.h"
#include "Bitmap.h"

class Triangle
{
private:
	Point a;
	Point b;
	Point c;

	Triangle(Point _a, Point _b, Point _c);
	double FindAngle(Line ab, Line bc);

public:
	Triangle(int fieldSize);
	bool IsAllowed();
	Bitmap DrawOn(Bitmap bitmap);
};