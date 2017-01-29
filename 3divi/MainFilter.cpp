#include "MainFilter.h"
#include "BicompFilter.h"
#include "MedianFilter.h"

MainFilter::MainFilter(Bitmap _bitmap) : bitmap(_bitmap) { }

Bitmap MainFilter::Process()
{
	auto noise = bitmap.GetNoise();
	auto result = bitmap;
	auto n = 0;

	if (noise == 0) return result;
	if (noise <= 1.5) n = 1;
	else if (noise <= 2.5) n = 2;
	else if (noise <= 3.5) n = 2;
	else if (noise <= 4.5) n = 3;
	else n = 4;

	for (auto i = 0; i < n; i++)
	{		
		auto mfilter = MedianFilter(result, 2, 6, 2);
		result = mfilter.Process();
	
		auto bfilter = BicompFilter(result, 3, 0);
		result = bfilter.Process();

		mfilter = MedianFilter(result, 2, 6, 2);
		result = mfilter.Process();
	}
	return result;
}