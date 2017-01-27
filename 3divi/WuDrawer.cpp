#include "WuDrawer.h"

double WuDrawer::FloatP(double x)
{
	if (x < 0)
		return 1 - (x - int(x));
	return x - int(x);
}

double WuDrawer::FloatPR(double x)
{
	return 1 - FloatP(x);
}

int WuDrawer::Round(double x)
{
	return int(x + 0.5);
}

WuDrawer::WuDrawer(Bitmap _bitmap) : bitmap(_bitmap) { }

void WuDrawer::Plot(Point pos, double c)
{
	bitmap[pos] = unsigned char((1 - c) * Bitmap::MAX_COLOR);
}

double WuDrawer::HandleEndpoint(Point point, double gradient, bool steep, Point& pxl)
{
	int xend = Round(point.x);
	double yend = point.y + gradient*(xend - point.x);
	double xgap = FloatP(point.x + 0.5);

	pxl = Point(xend, int(yend));

	if (steep)
	{
		Plot(Point(pxl.y, pxl.x), FloatPR(yend) * xgap);
		Plot(Point(pxl.y + 1, pxl.x), FloatP(yend) * xgap);
	}
	else
	{
		bitmap[Point(pxl.x, pxl.y)] = unsigned char(FloatPR(yend) * xgap);
		bitmap[Point(pxl.x, pxl.y + 1)] = unsigned char(FloatP(yend) * xgap);
	}
	return yend + gradient;
}

void WuDrawer::Process(Line line)
{
	bool steep = abs(line.end.y - line.start.y) > abs(line.end.x - line.start.x);

	if (steep)
		line.RotateY();
	if (line.end.x < line.start.x)
		line.RotateX();

	double dx = line.end.x - line.start.x;
	double dy = line.end.y - line.start.y;
	double gradient = dy / dx;

	Point xpl1, xpl2;
	double intery = HandleEndpoint(line.start, gradient, steep, xpl1);
	HandleEndpoint(line.end, gradient, steep, xpl2);

	if (steep)
	{
		for (int x = int(xpl1.x) + 1; x < xpl2.x - 1; x++)
		{
			Plot(Point(int(intery), x), FloatPR(intery));
			Plot(Point(int(intery) + 1, x), FloatP(intery));
			intery = intery + gradient;
		}
	}
	else
	{
		for (int x = int(xpl1.x) + 1; x < xpl2.x - 1; x++)
		{
			Plot(Point(x, int(intery)), FloatPR(intery));
			Plot(Point(x, int(intery) + 1), FloatP(intery));
			intery = intery + gradient;
		}
	}
}

