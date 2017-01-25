#include "BicompFilter.h"
#include <algorithm>

BicompFilter::Island::Island(int _count, int _curColor) : count(_count), currentColor(_curColor) { }

bool BicompFilter::Island::operator<(const Island& i) const
{
	return count < i.count;
}

BicompFilter::BicompFilter(Bitmap _bitmap, int _step, int _minshade)
	: step(_step), minshade(_minshade), color(_bitmap.Width(), _bitmap.Height()), bitmap(_bitmap) { }

bool BicompFilter::CheckPoint(Point point)
{
	return color[point] == 0 && bitmap[point] > minshade;
}

int BicompFilter::FloodFill(int currentColor, Point pivot)
{
	auto allowedNeighbors = std::vector<Point>();
	auto lookup = std::vector<Point>();
	lookup.push_back(pivot);	
	int count = 1;

	while (true)
	{
		int layerCount = 0;
		for (auto current : lookup)
		{
			color[current] = currentColor;			
			for (int x = std::max(int(current.x) - step, 0); x < std::min(int(current.x) + step, bitmap.Width()); x++)
				for (int y = std::max(int(current.y) - step, 0); y < std::min(int(current.y) + step, bitmap.Height()); y++)
				{
					auto p = Point(x, y);
					if (CheckPoint(p))
					{
						allowedNeighbors.push_back(p);
						color[p] = currentColor;
						layerCount++;
					}
				}
		}
		if (!layerCount) break;
		count += layerCount;
		lookup = std::vector<Point>(allowedNeighbors);
		allowedNeighbors.clear();
	}
	return count;
}

Bitmap BicompFilter::Process()
{
	int currentColor = 1;
	auto islands = std::vector<Island>();
	auto rbitmap = bitmap;

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