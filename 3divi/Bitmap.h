#pragma once
#include <string>
#include "Matrix.h"

class Bitmap : public Matrix<unsigned char>
{
public:
	static const int MIN_SHADE = 50;
	Bitmap(const int _width, const int _height);
	void Noise(const double prob);
	double GetNoise() const;
	void WriteToPGM(std::string filename);
	void ReadFromPGM(std::string filename);	
};
