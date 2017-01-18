#include "MainFilter.h"
#include "BicompFilter.h"
#include "MedianFilter.h"

MainFilter::MainFilter(Bitmap _bitmap) : bitmap(_bitmap) { }

Bitmap MainFilter::Process()
{
	double noise = bitmap.GetNoise();
	Bitmap result = bitmap;
	int n;

	if (noise == 0) n = 0;
	else if (noise <= 1.5) n = 1;
	else if (noise <= 2.5) n = 2;
	else if (noise <= 3.5) n = 2;
	else if (noise <= 4.5) n = 3;
	else n = 4;

	for (int i = 0; i < n; i++)
	{		
		MedianFilter mfilter = MedianFilter(result, 2, 6, 2);
		result = mfilter.Process();
	
		BicompFilter bfilter = BicompFilter(result, 3, 0);
		result = bfilter.Process();

		mfilter = MedianFilter(result, 2, 6, 2);
		result = mfilter.Process();
	}
	return result;
}