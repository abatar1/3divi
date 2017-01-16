#pragma once
#include <vector>
#include <complex>

class FFT
{
public:
	typedef std::complex<double> Complex;
	typedef std::vector<Complex> CArray;
	typedef std::vector<CArray> CMatrix;

	static CArray Transform(CArray x, bool isInversed);
	static CMatrix Transform2Dim(CMatrix c, bool isInversed);	
	static CMatrix MultiplyMatrix(CMatrix a, CMatrix b);
private:
	static int Permutation(int num, int logn);
	static void TransformLine(CMatrix& matrix, int fBound, int sBound, bool isInversed);
};
