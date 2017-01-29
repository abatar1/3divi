#include "WuDrawer.h"

double WuDrawer::FloatP(double x)
{
	return x < 0 ? 1 - (x - int(x)) : x - int(x);
}

double WuDrawer::FloatPR(double x)
{
	return 1 - FloatP(x);
}

int WuDrawer::Round(double x)
{
	return int(x + 0.5);
}

WuDrawer::WuDrawer(Bitmap _bitmap) : bitmap(_bitmap) {}

void WuDrawer::Plot(Point pos, double c)
{
	bitmap[pos] = unsigned char((1 - c) * Bitmap::MAX_COLOR);
}

double WuDrawer::HandleEndpoint(Point point, double gradient, bool steep, Point& pxl)
{
	auto xend = Round(point.x);
	auto yend = point.y + gradient*(xend - point.x);
	auto xgap = FloatP(point.x + 0.5);

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
	auto steep = abs(line.end.y - line.start.y) > abs(line.end.x - line.start.x);

	if (steep)
		line.RotateY();
	if (line.end.x < line.start.x)
		line.RotateX();

	auto dx = line.end.x - line.start.x;
	auto dy = line.end.y - line.start.y;
	auto gradient = dy / dx;

	Point xpl1, xpl2;
	auto intery = HandleEndpoint(line.start, gradient, steep, xpl1);
	HandleEndpoint(line.end, gradient, steep, xpl2);

	if (steep)
	{
		for (auto x = int(xpl1.x) + 1; x < xpl2.x - 1; x++)
		{
			Plot(Point(int(intery), x), FloatPR(intery));
			Plot(Point(int(intery) + 1, x), FloatP(intery));
			intery = intery + gradient;
		}
	}
	else
	{
		for (auto x = int(xpl1.x) + 1; x < xpl2.x - 1; x++)
		{
			Plot(Point(x, int(intery)), FloatPR(intery));
			Plot(Point(x, int(intery) + 1), FloatP(intery));
			intery = intery + gradient;
		}
	}
}

