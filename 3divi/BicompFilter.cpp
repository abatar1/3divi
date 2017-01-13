#include "BicompFilter.h"

BicompFilter::Island::Island(int _count, int _curColor) : count(_count), currentColor(_curColor) { }

bool BicompFilter::Island::operator<(const Island& i) const
{
	return count < i.count;
}

BicompFilter::BicompFilter(Bitmap _bitmap, int _step)
	: bitmap(_bitmap), color(_bitmap.Width(), _bitmap.Height()), step(_step) { }

bool BicompFilter::CheckPoint(Point point)
{
	return color[point] == 0 && bitmap[point] > 50;
}

int BicompFilter::FloodFill(int currentColor, Point pivot)
{
	int count = 1;
	vector<Point> lookup = vector<Point>();
	lookup.push_back(pivot);	

	while (lookup.size() > 0)
	{
		Point current = lookup.back();
		lookup.pop_back();

		if (color[current] != 0) 
			continue;
		color[current] = currentColor;
		count++;
		for (int x = max(int(current.x) - step, 0); x < min(int(current.x) + step, bitmap.Width()); x++)
			for (int y = max(int(current.y) - step, 0); y < min(int(current.y) + step, bitmap.Width()); y++)
			{
				Point p = Point(x, y);
				if (CheckPoint(p))
					lookup.push_back(p);
			}
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
			if (CheckPoint(p))
			{
				int count = FloodFill(currentColor, p);
				if (count > 1)
				{
					islands.push_back(Island(count, currentColor));
					currentColor++;
				}					
			}
		}
	int maxColor = Island(*max_element(islands.begin(), islands.end())).currentColor;
	for (int x = 0; x < bitmap.Width(); x++)
		for (int y = 0; y < bitmap.Height(); y++)
			if (color[Point(x, y)] != maxColor)
				rbitmap[Point(x, y)] = 0;
	return rbitmap;
}