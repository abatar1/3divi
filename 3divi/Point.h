#pragma once
#include <string>

class Point
{
public:
	double x;
	double y;

	Point(double _x, double _y);
	Point();
	Point(const int fieldSize);

	Point operator-(const Point& a);
	bool operator==(const Point& a);

	std::string ToString();
};