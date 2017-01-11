#pragma once
#include "Point.h"
#include "Bitmap.h"
#include "Line.h"

class WuDrawer
{
private:
	double HandleEndpoint(Point point, double gradient, bool steep, Point& pxl);
	void Plot(Point pos, double c);

public:
	Bitmap bitmap;
	WuDrawer(Bitmap _bitmap);
	void Process(Line line);
};