#define _USE_MATH_DEFINES
#include <algorithm>
#include "Matrix.h"
#include "HoughTransformator.h"

HoughTransformator::Cache::Cache(double theta)
{
	double deg2rad = M_PI / 180.0;
	sinT = sin(theta * deg2rad);
	cosT = cos(theta * deg2rad);
}

HoughTransformator::Cache::Cache()
{
	sinT = 0;
	cosT = 0;
}

HoughTransformator::HoughTransformator(Bitmap _bitmap) : bitmap(_bitmap)
{
	int bitmapH = bitmap.Height();
	int bitmapW = bitmap.Width();
	int hough_h = (int)((sqrt(2) * (double)(bitmapH > bitmapW ? bitmapH : bitmapW)) / 2);

	accumulator = Matrix<int>(degrees, hough_h * 2);
	caches = std::vector<Cache>(degrees);
	for (int i = 0; i < degrees; i++) caches[i] = Cache(i);
}

Matrix<int> HoughTransformator::Transform()
{
	int center_x = bitmap.Width() / 2;
	int center_y = bitmap.Height() / 2;
	int hough_h = accumulator.Height() / 2;

	for (int y = 0; y < bitmap.Height(); y++)
		for (int x = 0; x < bitmap.Width(); x++)
		{
			if (bitmap[x, y] != 0)
			{
				int x_dif = x - center_x, y_dif = y - center_y;
				for (int t = 0; t < degrees; t++)
				{					
					double r = round(x_dif * caches[t].cosT + y_dif * caches[t].sinT + hough_h);
					Point p = Point(t, r);
					accumulator[p] = accumulator[p] + 1;
				}
			}
		}
	return accumulator;
}

std::vector<Line> HoughTransformator::GetLines(int threshold)
{
	std::vector<Line> lines = std::vector<Line>();
	int bitmap_h2 = bitmap.Height() / 2;
	int bitmap_w2 = bitmap.Width() / 2;
	int accu_h2 = accumulator.Height() / 2;

	for (int r = 0; r < accumulator.Height(); r++)
	{
		for (int t = 0; t < accumulator.Width(); t++)
		{
			if (accumulator[t, r] >= threshold)
			{
				int max = accumulator[t, r];
				for (int ly = -4; ly <= 4; ly++)		
					for (int lx = -4; lx <= 4; lx++)
						if ((ly + r >= 0 && ly + r < accumulator.Height()) && (lx + t >= 0 && lx + t < accumulator.Width()))
						{
							if (accumulator[t + lx, r + ly] > max)
								max = accumulator[t + lx, r + ly];
							ly = lx = 5;
						}						

				if (max > accumulator[t, r]) continue;

				double x1, x2, y1, y2;
				double sint = caches[t].sinT;
				double cost = caches[t].cosT;

				if (t >= 45 && t <= 45 * 3)
				{
					x1 = 0;
					y1 = ((double)(r - accu_h2) - ((x1 - bitmap_w2) * cost)) / sint + bitmap_h2;

					x2 = bitmap.Width();
					y2 = ((double)(r - accu_h2) - ((x2 - bitmap_w2) * cost)) / sint + bitmap_h2;
				}
				else
				{
					y1 = 0;
					x1 = ((double)(r - accu_h2) - ((y1 - bitmap_h2) * sint)) / cost + bitmap_w2;

					y2 = bitmap.Height();
					x2 = ((double)(r - accu_h2) - ((y2 - bitmap_h2) * sint)) / cost + bitmap_w2;
				}
				lines.push_back(Line(Point(x1, y1), Point(x2, y2)));
			}
		}
	}
	return GetMaxNLines(lines, 3);
}

std::vector<Line> HoughTransformator::GetMaxNLines(std::vector<Line> lines, int n)
{
	std::sort(lines.begin(), lines.end());
	lines.resize(n);
	return lines;
}