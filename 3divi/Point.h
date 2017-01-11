#pragma once

class Point
{
public:
	double x;
	double y;

	Point(double _x, double _y);
	Point();
	Point(int fieldSize);

	Point operator-(const Point& a);
	bool operator==(const Point& a);
};