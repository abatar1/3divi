#include "MathExtention.h"

double MathExtention::FloatP(double x)
{
	if (x < 0)
		return 1 - (x - int(x));
	return x - int(x);
}

double MathExtention::FloatPR(double x)
{
	return 1 - FloatP(x);
}

int MathExtention::Round(double x)
{
	return int(x + 0.5);
}