#pragma once
#include <algorithm>
#include "Bitmap.h"

class BicompFilter
{
	int step;
	int corners;
	Matrix color;
	Bitmap bitmap;

	struct Island
	{
		int count;
		int currentColor;
		Point p;

		Island(int _count, int _curColor);
		bool operator<(const Island& i) const;
	};

	int FloodFill(int curColor, Point pivot);

public:
	BicompFilter(Bitmap _bitmap, int _step, int _corners);
	Bitmap Process();
};