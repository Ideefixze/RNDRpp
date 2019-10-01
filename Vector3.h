#pragma once
#include "iVector2.h"
#include <math.h>

class Vector2
{
public:
	float x, y;
	Vector2();
	Vector2(float x, float y);
};

class Vector3
{
public:
	float x, y, z;
	Vector3();
	Vector3(float x, float y, float z);

	Vector3 operator+(const Vector3& second) const;
	Vector3 operator-(const Vector3& second) const;
	void Normalize();

	Vector2 Get2D();

	~Vector3();
};

