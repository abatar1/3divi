#pragma once
#include <string>
#include "Matrix.h"

class Bitmap : public Matrix<unsigned char>
{
public:
	Bitmap(const int _width, const int _height);
	void Noise(const double prob);
	void WriteToPGM(std::string filename);
	void ReadFromPGM(std::string filename);
};
