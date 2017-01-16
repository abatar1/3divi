#pragma once
#define _USE_MATH_DEFINES
#include <algorithm>
#include "FFT.h"

using namespace std;

int FFT::Permutation(int num, int logn)
{
	int res = 0;
	for (int i = 0; i < logn; ++i)
		if (num & (1 << i))
			res |= 1 << (logn - 1 - i);
	return res;
}

FFT::CArray FFT::Transform(FFT::CArray a, bool isInversed) 
{
	int n = (int)a.size();
	CArray result = CArray(a);
	int lg_n = 0;
	while ((1 << lg_n) < n)  ++lg_n;

	for (int i = 0; i < n; ++i)
		if (i < Permutation(i, lg_n))
			swap(result[i], result[Permutation(i, lg_n)]);

	for (int len = 2; len <= n; len <<= 1) 
	{
		double ang = 2 * M_PI / len * (isInversed ? -1 : 1);
		Complex wlen(cos(ang), sin(ang));
		for (int i = 0; i<n; i += len) 
		{
			Complex w(1);
			for (int j = 0; j < len / 2; ++j) 
			{
				Complex u = result[i + j], v = result[i + j + len / 2] * w;
				result[i + j] = u + v;
				result[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}
	if (isInversed)
		for (int i = 0; i < n; ++i)
			result[i] /= n;
	return result;
}

void FFT::TransformLine(FFT::CMatrix& matrix, int fBound, int sBound, bool isInversed)
{
	CArray ca = CArray(sBound);
	for (int i = 0; i < fBound; i++)
	{
		for (int j = 0; j < sBound; j++) ca[i] = matrix[i][j];
		ca = Transform(ca, isInversed);
		for (int j = 0; j < sBound; j++) matrix[i][j] = ca[i];
	}
}

FFT::CMatrix FFT::Transform2Dim(FFT::CMatrix c, bool isInversed)
{
	const int nx = c.size();
	const int ny = c[0].size();
	CArray ca = CArray(nx);
	CMatrix result = CMatrix(c);

	TransformLine(result, ny, nx, isInversed);
	TransformLine(result, nx, ny, isInversed);

	return result;
}

FFT::CMatrix FFT::MultiplyMatrix(FFT::CMatrix a, CMatrix b)
{
	size_t n = a.size(), m = a[0].size();
	CMatrix result = CMatrix(n);
	for (size_t i = 0; i < n; i++)
	{
		result[i] = CArray(m);
		for (size_t j = 0; j < m; j++)
			result[i][j] = a[i][j] * b[i][j];
	}
	return result;
}
