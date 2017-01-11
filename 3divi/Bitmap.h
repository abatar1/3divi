#pragma once
#include <vector>
#include <string>
#include "Point.h"

using namespace std;

class Bitmap
{
	vector<vector<unsigned char>> bitmap;
	int width;
	int height;

	struct Proxy
	{
		Bitmap& b;
		Point indexer;

		Proxy(Bitmap& _bitmap, Point _indexer);
		operator unsigned char();
		unsigned char& operator=(const unsigned char& other);
	};

public:
	Bitmap(int _width, int _height);
	Bitmap operator=(const Bitmap& b);
	Proxy operator[](Point indexer);	
	void Noise(double prob);
	void WriteToPGM(string filename);
	void ReadFromPGM(string filename);
};
