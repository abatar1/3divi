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
	Matrix<int> accumulator;
	std::vector<Cache> caches;
	Bitmap bitmap;	

	std::vector<Line> GetMaxNLines(std::vector<Line>, int n);
public:
	HoughTransformator(Bitmap bitmap);
	Matrix<int> Transform();
	std::vector<Line> GetLines(int threshold);
};
