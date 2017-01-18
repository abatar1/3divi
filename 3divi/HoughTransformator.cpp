#pragma once
#define _USE_MATH_DEFINES
#include "Matrix.h"
#include "HoughTransformator.h"
#include <cmath>

HoughTransformator::Cache::Cache(double theta)
{
	sinT = sin(theta);
	cosT = cos(theta);
}
	
HoughTransformator::Cache::Cache()
{
	sinT = 0;
	cosT = 0;
}

std::vector<HoughTransformator::Cache> HoughTransformator::CreateTable()
{
	std::vector<Cache> table = std::vector<Cache>(181);
	double rad = (M_PI / 180);
	double theta = rad * -90;
	for (int i = 0; i < 181; i++)
	{
		table[i] = Cache(theta);
		theta += rad;
	}
	return table;
}

HoughTransformator::HoughTransformator(Bitmap _bitmap) : bitmap(_bitmap) { }

void HoughTransformator::Process()
{
	int D = (int)(sqrt(bitmap.Width() ^ 2 + bitmap.Height() ^ 2));
	Matrix<unsigned char> houghSpace = Matrix<unsigned char>(181, ((int)(1.414213562 * D) * 2) + 1);

	int xpoint = 0;
	unsigned char maxT = 0;
	std::vector<Cache> table = CreateTable();
	for (int x = 0; x < bitmap.Width(); x++)
		for (int y = 0; y < bitmap.Height(); y++)
		{
			if (bitmap[x, y] == 0) continue;

			for (int i = 0; i < 181; i++)
			{
				int rho = (int)((x * table[i].cosT + y * table[i].sinT)) + (houghSpace.Height() / 2);
				unsigned char g = houghSpace[i, rho] + 1;
				if (g > maxT)
				{
					maxT = g;
					xpoint = i;
				}
				houghSpace[i, rho] = g;
			}
		}
}

