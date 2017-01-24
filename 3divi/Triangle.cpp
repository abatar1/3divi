#define _USE_MATH_DEFINES
#include <fstream>
#include <iostream>
#include "Triangle.h"
#include "WuDrawer.h"
#include "HoughTransformator.h"

Triangle::Triangle() : a(0), b(0), c(0) {}

Triangle::Triangle(Point _a, Point _b, Point _c) : a(_a), b(_b), c(_c) {}

Triangle::Triangle(const int fieldSize)
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

Point Triangle::FindIntersection(Line ab, Line bc)
{
	Point s1 = ab.end - ab.start;
	Point s2 = bc.end - bc.start;
	double t = (s2.x * (ab.start.y - bc.start.y) - s2.y * (ab.start.x - bc.start.x)) / (-s2.x * s1.y + s1.x * s2.y);

	return Point(ab.start.x + (t * s1.x), ab.start.y + (t * s1.y));
}

Triangle Triangle::GetFromBitmap(Bitmap bitmap, int threshold)
{
	HoughTransformator ht = HoughTransformator(bitmap);
	Matrix<unsigned int> accum = ht.Transform();
	std::vector<Line> lines = ht.GetLines(threshold);
	Point a = FindIntersection(lines[0], lines[1]);
	Point b = FindIntersection(lines[0], lines[2]);
	Point c = FindIntersection(lines[1], lines[2]);

	return Triangle(a, b, c);
}

void Triangle::ToString()
{
	std::cout << a.ToString() << std::endl;
	std::cout << b.ToString() << std::endl;
	std::cout << c.ToString() << std::endl;
}

void Triangle::ToFile(std::string filename)
{
	std::ofstream file(filename, std::ios::out);
	file << a.ToString() << std::endl;
	file << b.ToString() << std::endl;
	file << c.ToString() << std::endl;
	file.close();
}