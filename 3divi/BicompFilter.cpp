#include "BicompFilter.h"

BicompFilter::Island::Island(int _count, int _curColor) : count(_count), currentColor(_curColor) { }

bool BicompFilter::Island::operator<(const Island& i) const
{
	return count < i.count;
}

BicompFilter::BicompFilter(Bitmap _bitmap, int _step, int _corners)
	: bitmap(_bitmap), color(_bitmap.Width(), _bitmap.Height()), step(_step), corners(_corners) { }

int BicompFilter::FloodFill(int curColor, Point pivot)
{
	int count = 1;
	vector<Point> lookup = vector<Point>();
	lookup.push_back(pivot);

	while (lookup.size() > 0)
	{
		Point current = lookup.back();
		lookup.pop_back();
		if (color[current] != 0 || bitmap[current] == 0)
			continue;
		color[current] = curColor;
		count++;
		for (int x = max(int(current.x) - step, 0); x < min(int(current.x) + step, bitmap.Width()); x++)
			for (int y = max(int(current.y) - step, 0); y < min(int(current.y) + step, bitmap.Width()); y++)
				if (corners)
					lookup.push_back(Point(x, y));
				else
					if (((x - int(current.x)) ^ 2 + (y - int(current.y)) ^ 2) < ((step - 1) ^ 2))
						lookup.push_back(Point(x, y));
	}
	return count;
}

Bitmap BicompFilter::Process()
{
	int currentColor = 1;
	vector<Island> islands = vector<Island>();
	Bitmap rbitmap = bitmap;

	for (int x = 0; x < bitmap.Width(); x++)
		for (int y = 0; y < bitmap.Height(); y++)
		{
			Point p = Point(x, y);
			if (bitmap[p] != 0)
			{
				int count = FloodFill(currentColor, p);
				islands.push_back(Island(count, currentColor));
				currentColor++;				
			}
		}
	sort(islands.begin(), islands.end());
	int maxCount = islands[0].count;
	for (int x = 0; x < bitmap.Width(); x++)
		for (int y = 0; y < bitmap.Height(); y++)
			if (color[Point(x, y)] != maxCount)
				rbitmap[Point(x, y)] = 0;
	return rbitmap;
}