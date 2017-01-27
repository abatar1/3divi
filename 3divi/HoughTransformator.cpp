#include <algorithm>
#include "Matrix.h"
#include "HoughTransformator.h"
#include "WuDrawer.h"

#define DEG2RAD 0.017453293f
#define DEGREES 180

HoughTransformator::Cache::Cache(double theta)
{
	sinT = sin(theta * DEG2RAD);
	cosT = cos(theta * DEG2RAD);
}

HoughTransformator::Cache::Cache()
{
	sinT = 0;
	cosT = 0;
}

HoughTransformator::HoughTransformator(Bitmap _bitmap, const int _step, int _threshold) : threshold(_threshold), step(_step), bitmap(_bitmap)
{
	int hough_h = static_cast<int>(sqrt(2.0) * (bitmap.Height() > bitmap.Width() ? bitmap.Height() : bitmap.Width()) / 2.0);
	accumulator = Matrix<int>(DEGREES, hough_h * 2);
	caches = std::vector<Cache>(DEGREES);
	for (int i = 0; i < DEGREES; i++) caches[i] = Cache(i);
}

Matrix<int> HoughTransformator::Transform()
{
	int center_x = bitmap.Width() / 2;
	int center_y = bitmap.Height() / 2;
	int accu_h2 = accumulator.Height() / 2;

	for (int y = 0; y < bitmap.Height(); y++)
		for (int x = 0; x < bitmap.Width(); x++)
		{
			if (!bitmap[Point(x, y)]) continue;
			
			int x_dif = x - center_x, y_dif = y - center_y;
			for (int t = 0; t < DEGREES; t++)
			{
				double r = round(x_dif * caches[t].cosT + y_dif * caches[t].sinT + accu_h2);
				accumulator[Point(t, r)] = accumulator[Point(t, r)] + 1;
			}		
		}
	return accumulator;
}

std::vector<Line> HoughTransformator::GetLines()
{
	auto lines = std::vector<Line>();
	int bitmap_h2 = bitmap.Height() / 2;
	int bitmap_w2 = bitmap.Width() / 2;
	int accu_h2 = accumulator.Height() / 2;

	while (true)
	{
		for (int r = 0; r < accumulator.Height(); r++)
		{
			for (int t = 0; t < accumulator.Width(); t++)
			{
				if (accumulator[Point(t, r)] >= threshold)
				{
					int max = accumulator[Point(t, r)];
					for (int ly = -step; ly <= step; ly++)
						for (int lx = -step; lx <= step; lx++)
							if (ly + r >= 0 && ly + r < accumulator.Height() && (lx + t >= 0 && lx + t < accumulator.Width()))
							{
								if (accumulator[Point(t + lx, r + ly)] > max)
								{
									max = accumulator[Point(t + lx, r + ly)];
									ly = lx = 5;
								}			
							}

					if (max > accumulator[Point(t, r)]) continue;

					double x1, y1, x2, y2;
					double sint = caches[t].sinT;
					double cost = caches[t].cosT;
					if (t >= DEGREES / 4 && t <= DEGREES / 4 * 3)
					{
						x1 = 0;
						y1 = (r - accu_h2 - (x1 - bitmap_w2) * cost) / sint + bitmap_h2;

						x2 = bitmap.Width() - 1;
						y2 = (r - accu_h2 - (x2 - bitmap_w2) * cost) / sint + bitmap_h2;
					}
					else
					{
						y1 = 0;
						x1 = (r - accu_h2 - (y1 - bitmap_h2) * sint) / cost + bitmap_w2;

						y2 = bitmap.Height() - 1;
						x2 = (r - accu_h2 - (y2 - bitmap_h2) * sint) / cost + bitmap_w2;
					}
					lines.push_back(Line(Point(x1, y1), Point(x2, y2)));
				}
			}
		}
		if (lines.size() > 3) threshold -= 10;
		if (lines.size() < 3) threshold += 10;
		if (lines.size() == 3) break;
	}
	return lines;
}