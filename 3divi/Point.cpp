#include <random> 
#include "Point.h"

Point::Point(double _x, double _y) : x(_x), y(_y) {}

Point::Point() {}

Point::Point(int fieldSize)
{
	std::tr1::random_device rd;
	std::tr1::mt19937 m1(rd());
	std::tr1::mt19937 m2(rd());
	std::tr1::uniform_real<double> distr(0, fieldSize);
	x = distr(m1), y = distr(m2);
}

Point Point::operator-(const Point& a)
{
	return Point(x - a.x, y - a.y);
}

bool Point::operator==(const Point& a)
{
	return x == a.x && y == a.y;
}

std::string Point::ToString()
{
	return std::to_string(x) + " " + std::to_string(y);
}
