#include <random> 
#include "Point.h"

using namespace std;

Point::Point(double _x, double _y) : x(_x), y(_y) {}

Point::Point() {}

Point::Point(int fieldSize)
{
	random_device rd;
	mt19937 m1(rd());
	mt19937 m2(rd());
	uniform_real<double> distr(0, fieldSize);
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
