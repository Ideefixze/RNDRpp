#include "stdafx.h"
#include "iVector2.h"
#include <math.h>
iVector2::iVector2(int x, int y)
{
	this->x = x;
	this->y = y;
}

float iVector2::DistanceTo(iVector2 destination)
{
	return sqrtf((x - destination.x)*(x - destination.x) + (y - destination.y)*(y - destination.y));
}


iVector2::~iVector2()
{
}
