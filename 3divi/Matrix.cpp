#include "Matrix.h"

Matrix::Matrix(int _width, int _height) : width(_width), height(_height)
{
	matrix = vector<vector<unsigned char>>(
		height,
		vector<unsigned char>(width, 0));
}

Matrix Matrix::operator=(const Matrix& b)
{
	matrix = b.matrix;
	width = b.width;
	height = b.height;
	return *this;
}

Matrix::Proxy Matrix::operator[](Point indexer)
{
	return Proxy(*this, indexer);
}

int Matrix::Width()
{
	return width;
}

int Matrix::Height()
{
	return height;
}

Matrix::Proxy::Proxy(Matrix& _bitmap, Point _indexer) : b(_bitmap), indexer(_indexer) { }

Matrix::Proxy::operator unsigned char()
{
	return b.matrix[int(indexer.x)][int(indexer.y)];
}

unsigned char& Matrix::Proxy::operator=(const unsigned char& other)
{
	return b.matrix[int(indexer.x)][int(indexer.y)] = other;
}