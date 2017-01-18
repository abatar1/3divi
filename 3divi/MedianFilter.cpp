#include "MedianFilter.h"

MedianFilter::MedianFilter(Bitmap _bitmap, int _step, int _thresold, int _count)
	:bitmap(_bitmap), step(_step), thresold(_thresold), count(_count) { }

int MedianFilter::CountNeighbors(Point current)
{
	int count = 0;
	for (int x = std::max(int(current.x) - step, 0); x < std::min(int(current.x) + step, bitmap.Width()); x++)
		for (int y = std::max(int(current.y) - step, 0); y < std::min(int(current.y) + step, bitmap.Height()); y++)
		{
			Point p = Point(x, y);
			if (bitmap[p] != 0)
				count++;
		}
	return count;
}

Bitmap MedianFilter::Process()
{
	Bitmap result = bitmap;
	for (int k = 0; k < count; k++)
	{
		for (int x = 0; x < bitmap.Width(); x++)
			for (int y = 0; y < bitmap.Height(); y++)
			{
				Point p = Point(x, y);
				if (CountNeighbors(p) < thresold) result[p] = 0;
			}
	}
	
	return result;
}
