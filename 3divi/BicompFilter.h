#pragma once
#include <algorithm>
#include "Bitmap.h"

class BicompFilter
{
	int step;
	int minshade;
	Matrix<int> color;
	Bitmap bitmap;

	struct Island
	{
		int count;
		int currentColor;

		Island(int _count, int _curColor);
		bool operator<(const Island& i) const;
	};

	int FloodFill(int curColor, Point pivot);
	bool CheckPoint(Point point);
public:
	BicompFilter(Bitmap _bitmap, int _step, int _minshade);
	Bitmap Process();
};