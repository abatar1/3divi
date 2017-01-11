#pragma once
#include <vector>
#include "Point.h"

using namespace std;

class Matrix
{
protected:
	vector<vector<unsigned char>> matrix;
	int width;
	int height;

	struct Proxy
	{
		Matrix& b;
		Point indexer;

		Proxy(Matrix& _matrix, Point _indexer);
		operator unsigned char();
		unsigned char& operator=(const unsigned char& other);
	};

public:
	Matrix(int _width, int _height);
	Matrix operator=(const Matrix& b);
	Proxy operator[](Point indexer);
	int Width();
	int Height();
};