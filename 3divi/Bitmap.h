#pragma once
#include <string>
#include "Matrix.h"

class Bitmap : public Matrix
{
public:
	Bitmap(int _width, int _height);
	void Noise(double prob);
	void WriteToPGM(std::string filename);
	void ReadFromPGM(std::string filename);
};
