#include "WuDrawer.h"
#include "MathExtention.h"

WuDrawer::WuDrawer(Bitmap _bitmap) : bitmap(_bitmap) { }

void WuDrawer::Plot(Point pos, double c)
{
	bitmap[pos] = unsigned char((1 - c) * 255);
}

double WuDrawer::HandleEndpoint(Point point, double gradient, bool steep, Point& pxl)
{
	int xend = MathExtention::Round(point.x);
	double yend = point.y + gradient*(xend - point.x);
	double xgap = 1 - MathExtention::FloatP(point.x + 0.5);

	pxl = Point(xend, int(yend));

	if (steep)
	{
		Plot(Point(pxl.y, pxl.x), MathExtention::FloatPR(yend) * xgap);
		Plot(Point(pxl.y + 1, pxl.x), MathExtention::FloatP(yend) * xgap);
	}
	else
	{
		bitmap[Point(pxl.x, pxl.y)] = unsigned char(MathExtention::FloatPR(yend) * xgap);
		bitmap[Point(pxl.x, pxl.y + 1)] = unsigned char(MathExtention::FloatP(yend) * xgap);
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
			Plot(Point(int(intery), x), MathExtention::FloatPR(intery));
			Plot(Point(int(intery) + 1, x), MathExtention::FloatP(intery));
			intery = intery + gradient;
		}
	}
	else
	{
		for (int x = int(xpl1.x) + 1; x < xpl2.x - 1; x++)
		{
			Plot(Point(x, int(intery)), MathExtention::FloatPR(intery));
			Plot(Point(x, int(intery) + 1), MathExtention::FloatP(intery));
			intery = intery + gradient;
		}
	}
}