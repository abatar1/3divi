#include <fstream>
#include <iostream>
#include "Triangle.h"
#include "WuDrawer.h"
#include "HoughTransformator.h"

Triangle::Triangle() : a(0), b(0), c(0) {}

Triangle::Triangle(Point _a, Point _b, Point _c) : a(_a), b(_b), c(_c) {}

Triangle::Triangle(const int fieldSize)
{
	auto t = Triangle(Point(fieldSize), Point(fieldSize), Point(fieldSize));
	while (!t.IsAllowed())
		t = Triangle(Point(fieldSize), Point(fieldSize), Point(fieldSize));
	*this = t;
}

bool Triangle::IsAllowed()
{
	auto AB = Line(a, b);
	auto AC = Line(a, c);
	auto BC = Line(b, c);
	if (AB.Length() < 100 || AC.Length() < 100 || BC.Length() < 100)
		return false;
	if (AB.FindAngle(AC) < 30 || AB.FindAngle(BC) < 30 || AC.FindAngle(BC) < 30)
		return false;
	return true;
}

Bitmap Triangle::DrawOn(Bitmap bitmap)
{
	auto drawer = WuDrawer(bitmap);
	drawer.Process(Line(a, b));
	drawer.Process(Line(a, c));
	drawer.Process(Line(b, c));
	return drawer.bitmap;
}

Triangle Triangle::GetFromBitmap(Bitmap bitmap, int step, int threshold)
{
	auto ht = HoughTransformator(bitmap, step);
	auto accum = ht.Transform();
	auto lines = ht.GetLines(threshold);
	auto a = lines[0].FindIntersection(lines[1]);
	auto b = lines[0].FindIntersection(lines[2]);
	auto c = lines[1].FindIntersection(lines[2]);

	return Triangle(a, b, c);
}

std::string Triangle::ToString()
{
	return a.ToString() + "\n" + b.ToString() + "\n" + c.ToString() + "\n";
}

void Triangle::ToFile(std::string filename)
{
	std::ofstream file(filename, std::ios::out);
	file << a.ToString() << std::endl;
	file << b.ToString() << std::endl;
	file << c.ToString() << std::endl;
	file.close();
}
