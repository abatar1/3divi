#include "BicompFilter.h"

using namespace std;

BicompFilter::Island::Island(int _count, int _curColor) : count(_count), currentColor(_curColor) { }

bool BicompFilter::Island::operator<(const Island& i) const
{
	return count < i.count;
}

BicompFilter::BicompFilter(int _step, int _minshade)
	: step(_step), minshade(_minshade) { }

bool BicompFilter::CheckPoint(Bitmap bitmap, Matrix<int> color, Point point)
{
	return color[point] == 0 && bitmap[point] > minshade;
}

int BicompFilter::FloodFill(Bitmap bitmap, Matrix<int> color, int currentColor, Point pivot)
{
	vector<Point> allowedNeighbors = vector<Point>();
	vector<Point> lookup = vector<Point>();
	lookup.push_back(pivot);	
	int count = 1;

	while (1)
	{
		int layerCount = 0;
		for (auto current : lookup)
		{
			color[current] = currentColor;			
			for (int x = max(int(current.x) - step, 0); x < min(int(current.x) + step, bitmap.Width()); x++)
				for (int y = max(int(current.y) - step, 0); y < min(int(current.y) + step, bitmap.Height()); y++)
				{
					Point p = Point(x, y);
					if (CheckPoint(bitmap, color, p))
					{
						allowedNeighbors.push_back(p);
						color[p] = currentColor;
						layerCount++;
					}
				}
		}
		if (!layerCount) break;
		count += layerCount;
		lookup = vector<Point>(allowedNeighbors);
		allowedNeighbors.clear();
	}
	return count;
}

Bitmap BicompFilter::Process(Bitmap bitmap)
{
	int currentColor = 1;
	vector<Island> islands = vector<Island>();
	Bitmap rbitmap = bitmap;
	Matrix<int> color = Matrix<int>(bitmap.Width(), bitmap.Height());

	for (int x = 0; x < bitmap.Width(); x++)
		for (int y = 0; y < bitmap.Height(); y++)
		{
			Point p = Point(x, y);
			if (CheckPoint(bitmap, color, p))
			{
				int count = FloodFill(bitmap, color, currentColor, p);
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