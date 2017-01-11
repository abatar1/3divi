#define _USE_MATH_DEFINES
#include "Triangle.h"
#include "WuDrawer.h"

Triangle::Triangle(Point _a, Point _b, Point _c) : a(_a), b(_b), c(_c) {}

Triangle::Triangle(int fieldSize)
{
	Triangle t = Triangle(Point(fieldSize), Point(fieldSize), Point(fieldSize));
	while (!t.IsAllowed())
		t = Triangle(Point(fieldSize), Point(fieldSize), Point(fieldSize));
	*this = t;
}

double Triangle::FindAngle(Line ab, Line bc)
{
	Point AB = ab.end - ab.start;
	Point BC = bc.end - bc.start;
	return acos(abs(AB.x*BC.x + AB.y*BC.y) / (sqrt(pow(AB.x, 2) + pow(AB.y, 2)) * sqrt(pow(BC.x, 2) + pow(BC.y, 2)))) * 180.0 / M_PI;
}

bool Triangle::IsAllowed()
{
	Line AB = Line(a, b);
	Line AC = Line(a, c);
	Line BC = Line(b, c);
	if (AB.Length() < 100 || AC.Length() < 100 || BC.Length() < 100)
		return false;
	if (FindAngle(AB, AC) < 30 || FindAngle(AB, BC) < 30 || FindAngle(AC, BC) < 30)
		return false;
	return true;
}

Bitmap Triangle::DrawOn(Bitmap bitmap)
{
	WuDrawer drawer = WuDrawer(bitmap);
	drawer.Process(Line(a, b));
	drawer.Process(Line(a, c));
	drawer.Process(Line(b, c));
	return drawer.bitmap;
}
