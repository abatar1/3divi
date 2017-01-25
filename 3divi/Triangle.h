#pragma once
#include "Point.h"
#include "Line.h"
#include "Bitmap.h"

class Triangle
{
	Point a;
	Point b;
	Point c;

	Triangle(Point _a, Point _b, Point _c);
	double FindAngle(Line ab, Line bc);
	static Point FindIntersection(Line ab, Line bc);
public:
	Triangle();
	explicit Triangle(const int fieldSize);
	bool IsAllowed();
	Bitmap DrawOn(Bitmap bitmap);
	Triangle GetFromBitmap(Bitmap bitmap, int step, int threshold);
	std::string ToString();
	void ToFile(std::string filename);
};