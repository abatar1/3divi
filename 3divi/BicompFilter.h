#pragma once
#include <algorithm>
#include "Bitmap.h"

class BicompFilter
{
	int step;
	int minshade;

	struct Island
	{
		int count;
		int currentColor;

		Island(int _count, int _curColor);
		bool operator<(const Island& i) const;
	};


	int FloodFill(Bitmap bitmap, Matrix<int> color, int curColor, Point pivot);
	bool CheckPoint(Bitmap bitmap, Matrix<int> color, Point point);
public:
	BicompFilter(int _step, int _minshade);
	Bitmap Process(Bitmap bitmap);
};