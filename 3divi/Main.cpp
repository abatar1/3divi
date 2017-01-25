#include <iostream>
#include <time.h>
#include "Bitmap.h"
#include "Triangle.h"
#include "MainFilter.h"

int main(int argc, char* argv[])
{
	const auto fieldSize = 500;
	auto prob = 0.0;
	clock_t timer1, timer2;
	/*if (argv[1] == "generator")
	{*/
		timer1 = clock();

		auto bitmap = Bitmap(fieldSize, fieldSize);
		auto triangle = Triangle(fieldSize);
		bitmap = triangle.DrawOn(bitmap);
		bitmap.Noise(prob);
		bitmap.WriteToPGM("image.pgm");

		timer2 = clock();
		std::cout << triangle.ToString();
		std::cout << (timer2 - timer1) / (CLOCKS_PER_SEC / 1000) << "ms" << std::endl;
	/*}
	else if (argv[1] == "restore")
	{*/
		timer1 = clock();

		auto newBitmap = Bitmap(fieldSize, fieldSize);
		newBitmap.ReadFromPGM("image.pgm");
		auto mFilter = MainFilter(newBitmap);
		newBitmap = mFilter.Process();
		auto triangle1 = Triangle();
		triangle1.GetFromBitmap(newBitmap, 4, 150);	
		triangle1.ToFile("output.txt");

		timer2 = clock();
		std::cout << (timer2 - timer1) / (CLOCKS_PER_SEC / 1000) << "ms" << std::endl;
	/*}*/
	return 0;
}