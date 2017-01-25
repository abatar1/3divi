#pragma once
#include "Point.h"
#include "Bitmap.h"
#include "Line.h"

class WuDrawer
{
	double HandleEndpoint(Point point, double gradient, bool steep, Point& pxl);
	void Plot(Point pos, double c);
	double FloatP(double x);
	double FloatPR(double x);
	int Round(double x);
public:
	Bitmap bitmap;
	WuDrawer(Bitmap _bitmap);
	void Process(Line line);
};