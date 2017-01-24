#pragma once
#include "Bitmap.h"
#include "Line.h"
#include <vector>

class HoughTransformator
{
private:
	struct Cache
	{
		double sinT;
		double cosT;

		Cache(double theta);
		Cache();
	};
	const int degrees = 180;
	Matrix<unsigned int> accumulator;
	std::vector<Cache> caches;
	Bitmap bitmap;	
public:
	HoughTransformator(Bitmap bitmap);
	Matrix<unsigned int> Transform();
	std::vector<Line> GetLines(int threshold);
};
