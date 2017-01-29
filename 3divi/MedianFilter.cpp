#include "MedianFilter.h"
#include <algorithm>

MedianFilter::MedianFilter(Bitmap _bitmap, int _step, int _thresold, int _count)
	:bitmap(_bitmap), step(_step), thresold(_thresold), count(_count) { }

int MedianFilter::CountNeighbors(Point current)
{
	auto count = 0;
	for (auto x = std::max(int(current.x) - step, 0); x < std::min(int(current.x) + step, bitmap.Width()); x++)
		for (auto y = std::max(int(current.y) - step, 0); y < std::min(int(current.y) + step, bitmap.Height()); y++)
		{
			auto p = Point(x, y);
			if (bitmap[p] != 0)
				count++;
		}
	return count;
}

Bitmap MedianFilter::Process()
{
	auto result = bitmap;
	for (auto k = 0; k < count; k++)
	{
		for (auto x = 0; x < bitmap.Width(); x++)
			for (auto y = 0; y < bitmap.Height(); y++)
			{
				auto p = Point(x, y);
				if (CountNeighbors(p) < thresold) result[p] = 0;
			}
	}
	
	return result;
}
