#include <iostream>
#include <time.h>
#include "Bitmap.h"
#include "Triangle.h"
#include "BicompFilter.h"
#include "MedianFilter.h"

int main(int argc, char* argv[])
{
	const int fieldSize = 500;
	double prob = 0.3;
	clock_t timer1, timer2;
	/*if (argv[1] == "generator")
	{*/
		timer1 = clock();

		Bitmap bitmap = Bitmap(fieldSize, fieldSize);
		Triangle triangle = Triangle(fieldSize);
		bitmap = triangle.DrawOn(bitmap);
		bitmap.Noise(prob);
		bitmap.WriteToPGM("image.pgm");

		timer2 = clock();
		std::cout << (timer2 - timer1) / (CLOCKS_PER_SEC / 1000) << "ms" << std::endl;
	/*}
	else if (argv[1] == "restore")
	{*/
		timer1 = clock();

		Bitmap newBitmap = Bitmap(fieldSize, fieldSize);
		newBitmap.ReadFromPGM("image.pgm");

		MedianFilter mfilter = MedianFilter(newBitmap, 2, 6, 2);
		Bitmap fBitmap = mfilter.Process();

		BicompFilter bfilter = BicompFilter(fBitmap, 3, 0);
		fBitmap = bfilter.Process();

		mfilter = MedianFilter(fBitmap, 2, 6, 2);
		fBitmap = mfilter.Process();

		fBitmap.WriteToPGM("result.pgm");

		timer2 = clock();
		std::cout << (timer2 - timer1) / (CLOCKS_PER_SEC / 1000) << "ms" << std::endl;
	/*}*/
	return 0;
}