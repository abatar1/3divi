#include <random> 
#include <fstream>
#include <cmath>
#include "Bitmap.h"

using namespace std;

Bitmap::Bitmap(const int _width, const int _height) : Matrix::Matrix(_width, _height) { }

void Bitmap::Noise(const double prob)
{
	if (!prob) return;

	random_device rd;
	mt19937 m(rd());
	uniform_real<double> distr1(0, 1);
	uniform_int<int> distr2(0, 255);
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

	return floor(sb / n / 255 * 2 * 100) / 100;
}

void Bitmap::WriteToPGM(string filename)
{
	ofstream f(filename, ios_base::out | ios_base::binary);
	int maxColorValue = 255;
	f << "P5\r\n" << width << " " << height << "\r\n" << maxColorValue << "\r\n";

	for (auto line : matrix)
		for (auto point : line)
			f.write(reinterpret_cast<const char*>(&point), sizeof(unsigned char));

	f.close();
}

void Bitmap::ReadFromPGM(string filename)
{
	ifstream f(filename, ios_base::in | ios_base::binary);
	string inputline;

	f.ignore(256, '\n');
	f.ignore(256, '\n');
	f.ignore(256, '\n');
	for (int i = 0; i < height; i++)
		f.read((char*)&matrix[i][0], width * sizeof(unsigned char));

	f.close();
}