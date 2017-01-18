#pragma once
#include "Bitmap.h"
#include <vector>

class HoughTransformator
{
	Bitmap bitmap;

	struct Cache
	{
		double sinT;
		double cosT;

		Cache(double theta);
		Cache();
	};

	std::vector<Cache> CreateTable();

public:
	HoughTransformator(Bitmap _bitmap);
	void Process();
};
