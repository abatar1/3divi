#pragma once
#include <vector>
#include "Point.h"

template <class Type>
class Matrix
{
protected:
	std::vector<std::vector<Type>> matrix;
	int width;
	int height;

	struct Proxy
	{
		Matrix<Type>& b;
		Point indexer;

		Proxy(Matrix& _bitmap, Point _indexer) : b(_bitmap), indexer(_indexer) { }

		operator int() const
		{
			return b.matrix[int(indexer.y)][int(indexer.x)];
		}

		Type& operator=(const Type& other)
		{
			return b.matrix[int(indexer.y)][int(indexer.x)] = other;
		};
	};
public:
	Matrix() : width(0) , height(0)
	{
		matrix = std::vector<std::vector<Type>>();
	}

	Matrix(int _width, int _height) : width(_width), height(_height)
	{
		matrix = std::vector<std::vector<Type>>(
			height,
			std::vector<Type>(width, 0));
	}

	Matrix operator=(const Matrix& b)
	{
		matrix = b.matrix;
		width = b.width;
		height = b.height;
		return *this;
	}

	Proxy operator[](Point indexer)
	{
		return Proxy(*this, indexer);
	}

	int Width() const
	{
		return width;
	}

	int Height() const
	{
		return height;
	}
};