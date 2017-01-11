#include "Bitmap.h"
#include "Triangle.h"
#include "BicompFilter.h"

int main(int argc, char* argv[])
{
	int fieldSize = 500;
	double prob = 0.2;

	Bitmap bitmap = Bitmap(fieldSize, fieldSize);

	/*if (argv[1] == "generator")
	{*/
		Triangle triangle = Triangle(fieldSize);
		bitmap = triangle.DrawOn(bitmap);
		bitmap.Noise(prob);
		bitmap.WriteToPGM("image.pgm");
	/*}
	else if (argv[1] == "restore")
	{*/
		bitmap.ReadFromPGM("image.pgm");
		BicompFilter bfilter = BicompFilter(bitmap, 2, 1);
		Bitmap fBitmap = bfilter.Process();
		fBitmap.WriteToPGM("result.pgm");
	/*}*/
	return 0;
}