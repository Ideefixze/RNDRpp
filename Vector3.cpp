#include "stdafx.h"
#include "Vector3.h"


Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2()
{
	this->x = 0;
	this->y = 0;
}


Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector2 Vector3::Get2D()
{
	return Vector2(x, y);
}

Vector3 Vector3::operator+(const Vector3& second) const
{
	Vector3 newvec(this->x + second.x, this->y + second.y, this->z + second.z);
	return newvec;
}


Vector3::~Vector3()
{
}
