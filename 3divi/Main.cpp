#include "Bitmap.h"
#include "Triangle.h"

int main(int argc, char* argv[])
{
	int fieldSize = 500;
	double prob = 0.0;

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
		bitmap.ReadFromPGM(argv[2]);
	/*}*/
	return 0;
}