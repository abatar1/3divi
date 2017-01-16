#pragma once
#include <vector>
#include "Point.h"

using namespace std;

template <class Type>
class Matrix
{
protected:
	vector<vector<Type>> matrix;
	int width;
	int height;

	struct Proxy
	{
		Matrix<Type>& b;
		Point indexer;

		Proxy(Matrix& _bitmap, Point _indexer) : b(_bitmap), indexer(_indexer) { }

		operator int()
		{
			return b.matrix[int(indexer.x)][int(indexer.y)];
		}

		Type& operator=(const Type& other)
		{
			return b.matrix[int(indexer.x)][int(indexer.y)] = other;
		};
	};

public:
	Matrix(int _width, int _height) : width(_width), height(_height)
	{
		matrix = vector<vector<Type>>(
			height,
			vector<Type>(width, 0));
	}

	Matrix operator=(const Matrix& b)
	{
		matrix = b.matrix;
		width = b.width;
		height = b.height;
		return *this;
	}

	typename Proxy operator[](Point indexer)
	{
		return Proxy(*this, indexer);
	}

	int Width()
	{
		return width;
	}

	int Height()
	{
		return height;
	}
};