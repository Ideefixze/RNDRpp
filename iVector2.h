#pragma once
class iVector2
{
public:
	int x;
	int y;

	iVector2(int x, int y);
	float DistanceTo(iVector2 destination);
	~iVector2();
};

