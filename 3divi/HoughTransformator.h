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

	const int step;
	Matrix<int> accumulator;
	std::vector<Cache> caches;
	Bitmap bitmap;	

	std::vector<Line> GetMaxNLines(std::vector<Line>, int n);
	std::vector<Line> RemoveAccumulations(std::vector<Line> lines, int threshold);
public:
	HoughTransformator(Bitmap bitmap, int step);
	Matrix<int> Transform();
	std::vector<Line> GetLines(int threshold);	
};
