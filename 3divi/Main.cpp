#include "Bitmap.h"
#include "Triangle.h"
#include "MainFilter.h"

int main(int argc, char* argv[])
{
	const auto fieldSize = 500;
	auto bitmap = Bitmap(fieldSize, fieldSize);

	if (!strcmp(argv[1], "generator"))
	{
		auto prob = strtod(argv[2], nullptr);
		auto triangle = Triangle(fieldSize);
		bitmap = triangle.DrawOn(bitmap);
		bitmap.Noise(prob);
		bitmap.WriteToPGM("image.pgm");
		triangle.ToFile("real.txt");
	}
	else if (!strcmp(argv[1], "restore"))
	{
		bitmap.ReadFromPGM(argv[2]);
		auto mFilter = MainFilter(bitmap);
		bitmap = mFilter.Process();
		bitmap.WriteToPGM("clear.pgm");
		auto triangle = Triangle();
		triangle.GetFromBitmap(bitmap, 4, 100);	
		triangle.ToFile("output.txt");
	}
	return 0;
}