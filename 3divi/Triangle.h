#pragma once
#include <string>
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
	Point FindIntersection(Line ab, Line bc);

public:
	Triangle();
	Triangle(const int fieldSize);
	bool IsAllowed();
	Bitmap DrawOn(Bitmap bitmap);
	Triangle GetFromBitmap(Bitmap bitmap, int threshold);
	void ToString();
	void ToFile(std::string filename);
};