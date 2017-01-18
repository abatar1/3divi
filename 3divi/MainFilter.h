#pragma once
#include "BicompFilter.h"
#include "MedianFilter.h"
#include "Bitmap.h"

class MainFilter
{
public:
	Bitmap Process(Bitmap bitmap)
	{
		double noise = bitmap.GetNoise();
		Bitmap result = Bitmap(bitmap);
		int n;

		if (noise == 0) return result;
		else if (noise <= 1.5) n = 1;
		else if (noise <= 2.5) n = 2;
		else if (noise <= 3.5) n = 2;
		else if (noise <= 4.5) n = 3;
		else if (noise <= 5.5) n = 4;

		for (int i = 0; i < n; i++)
		{
			BicompFilter bfilter = BicompFilter(3, 0);
			MedianFilter mfilter = MedianFilter(2, 6, 2);

			result = bfilter.Process(result);
			result = mfilter.Process(result);
			result = bfilter.Process(result);
		}
	}
};