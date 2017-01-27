#include <random> 
#include <fstream>
#include <cmath>
#include "Bitmap.h"

Bitmap::Bitmap(const int _width, const int _height) : Matrix::Matrix(_width, _height) {}

Bitmap::Bitmap() {}

void Bitmap::Noise(const double prob)
{
	if (!prob) return;

	std::random_device rd;
	std::mt19937 m(rd());
	std::uniform_real<double> distr1(0, 1);
	std::uniform_int<int> distr2(0, MAX_COLOR);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (distr1(m) - prob < 0) matrix[i][j] = distr2(m);
}

double Bitmap::GetNoise() const
{
	int n = width * height;
	double sb = 0;

	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++) sb += matrix[y][x];

	return floor(sb / n / MAX_COLOR * 2 * 100) / 100;
}

void Bitmap::WriteToPGM(std::string filename)
{
	std::ofstream f(filename, std::ios_base::out | std::ios_base::binary);
	f << "P5\r\n" << width << " " << height << "\r\n" << MAX_COLOR << "\r\n";

	for (auto line : matrix)
		for (auto point : line)
			f.write(reinterpret_cast<const char*>(&point), sizeof(unsigned char));

	f.close();
}

void Bitmap::ReadFromPGM(std::string filename)
{
	std::ifstream f(filename, std::ios_base::in | std::ios_base::binary);

	f.ignore(256, '\n');
	f.ignore(256, '\n');
	f.ignore(256, '\n');
	for (int i = 0; i < height; i++)
		f.read(reinterpret_cast<char*>(&matrix[i][0]), width * sizeof(unsigned char));

	f.close();
}