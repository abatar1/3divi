#pragma once
#include "Bitmap.h"

class MainFilter
{
	Bitmap bitmap;
public:
	MainFilter(Bitmap _bitmap);
	Bitmap Process();
};