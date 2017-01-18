#pragma once
#include <algorithm>
#include "Bitmap.h"

using namespace std;

class MedianFilter
{
	int step;
	int thresold;
	int count;

	int CountNeighbors(Bitmap bitmap, Point current);
public:
	MedianFilter(int _step, int _thresold, int _count);
	Bitmap Process(Bitmap bitmap);
};
