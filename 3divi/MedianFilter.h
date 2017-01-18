#pragma once
#include <algorithm>
#include "Bitmap.h"

class MedianFilter
{
	Bitmap bitmap;
	int step;
	int thresold;
	int count;

	int CountNeighbors(Point current);
public:
	MedianFilter(Bitmap _bitmap, int _step, int _thresold, int _count);
	Bitmap Process();
};
