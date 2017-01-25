#pragma once
#include <string>

class Point
{
public:
	double x;
	double y;

	Point(double _x, double _y);
	Point();
	explicit Point(const int fieldSize);

	Point operator-(const Point& a) const;
	bool operator==(const Point& a) const;

	std::string ToString() const;
};