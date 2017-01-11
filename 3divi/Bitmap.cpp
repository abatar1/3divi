#include <random> 
#include <fstream>
#include "Bitmap.h"

Bitmap::Bitmap(int _width, int _height) : width(_width), height(_height)
{
	bitmap = vector<vector<unsigned char>>(
		height,
		vector<unsigned char>(width, 0));
}

Bitmap Bitmap::operator=(const Bitmap& b)
{
	bitmap = b.bitmap;
	width = b.width;
	height = b.height;
	return *this;
}

Bitmap::Proxy Bitmap::operator[](Point indexer)
{
	return Proxy(*this, indexer);
}

void Bitmap::Noise(double prob)
{
	random_device rd;
	mt19937 m(rd());
	uniform_real<double> distr1(0, 1);
	uniform_int<int> distr2(0, 255);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (distr1(m) - prob < 0) bitmap[i][j] = distr2(m);
}

void Bitmap::WriteToPGM(string filename)
{
	ofstream f(filename, ios_base::out | ios_base::binary);
	int maxColorValue = 255;
	f << "P5\r\n" << width << " " << height << "\r\n" << maxColorValue << "\r\n";

	for (auto line : bitmap)
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
		f.read((char*)&bitmap[i][0], width * sizeof(unsigned char));
}

Bitmap::Proxy::Proxy(Bitmap& _bitmap, Point _indexer) : b(_bitmap), indexer(_indexer) { }

Bitmap::Proxy::operator unsigned char()
{
	return b.bitmap[int(indexer.x)][int(indexer.y)];
}

unsigned char& Bitmap::Proxy::operator=(const unsigned char& other)
{
	return b.bitmap[int(indexer.x)][int(indexer.y)] = other;
}