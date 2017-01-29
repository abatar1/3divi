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

HoughTransformator::HoughTransformator(Bitmap _bitmap, const int _step, int _threshold) 
	: threshold(_threshold), step(_step), centerBY(_bitmap.Height() / 2), centerBX(_bitmap.Width() / 2), bitmap(_bitmap)
{
	centerA = static_cast<int>(sqrt(2.0) * (bitmap.Height() > bitmap.Width() ? bitmap.Height() : bitmap.Width()) / 2.0);
	accumulator = Matrix<int>(DEGREES, centerA * 2);
	caches = std::vector<Cache>(DEGREES);
	for (auto i = 0; i < DEGREES; i++) caches[i] = Cache(i);
}

Matrix<int> HoughTransformator::Transform()
{
	for (auto y = 0; y < bitmap.Height(); y++)
		for (auto x = 0; x < bitmap.Width(); x++)
		{
			if (!bitmap[Point(x, y)]) continue;
			
			auto x_dif = x - centerBX, y_dif = y - centerBY;
			for (auto t = 0; t < DEGREES; t++)
			{
				auto r = round(x_dif * caches[t].cosT + y_dif * caches[t].sinT + centerA);
				accumulator[Point(t, r)] = accumulator[Point(t, r)] + 1;
			}		
		}
	return accumulator;
}

std::vector<Line> HoughTransformator::GetLines()
{
	auto lines = std::vector<Line>();
	while (true)
	{
		for (auto r = 0; r < accumulator.Height(); r++)
		{
			for (auto t = 0; t < accumulator.Width(); t++)
			{
				if (accumulator[Point(t, r)] >= threshold)
				{
					int max = accumulator[Point(t, r)];
					for (auto ly = -step; ly <= step; ly++)
						for (auto lx = -step; lx <= step; lx++)
							if (ly + r >= 0 && ly + r < accumulator.Height() && (lx + t >= 0 && lx + t < accumulator.Width()))
							{
								if (accumulator[Point(t + lx, r + ly)] > max)
								{
									max = accumulator[Point(t + lx, r + ly)];
									ly = lx = step + 1;
								}			
							}

					if (max > accumulator[Point(t, r)]) continue;

					double x1, y1, x2, y2;
					auto sint = caches[t].sinT;
					auto cost = caches[t].cosT;
					if (t >= DEGREES / 4 && t <= DEGREES / 4 * 3)
					{
						x1 = 0;
						y1 = (r - centerA - (x1 - centerBX) * cost) / sint + centerBY;

						x2 = bitmap.Width();
						y2 = (r - centerA - (x2 - centerBX) * cost) / sint + centerBY;
					}
					else
					{
						y1 = 0;
						x1 = (r - centerA - (y1 - centerBY) * sint) / cost + centerBX;

						y2 = bitmap.Height();
						x2 = (r - centerA - (y2 - centerBY) * sint) / cost + centerBX;
					}
					lines.push_back(Line(Point(x1, y1), Point(x2, y2)));
				}
			}
		}
		if (lines.size() > 3) threshold += 10;
		if (lines.size() < 3) threshold -= 10;
		if (lines.size() == 3) break;
	}
	return lines;
}