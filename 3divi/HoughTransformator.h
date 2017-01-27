#pragma once
#include "Bitmap.h"
#include "Line.h"
#include <vector>

class HoughTransformator
{
	struct Cache
	{
		double sinT;
		double cosT;
		Cache(double theta);
		Cache();
	};
	int threshold;
	const int step;
	Matrix<int> accumulator;
	std::vector<Cache> caches;
	Bitmap bitmap;	
public:
	HoughTransformator(Bitmap bitmap, const int step, int threshold);
	Matrix<int> Transform();
	std::vector<Line> GetLines();
};
