#include "stdafx.h"
#include "Color.h"


Color::Color()
{
	r = 0;
	g = 0;
	b = 0;
	a = 255;
}

Color::Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	r = red;
	g = green;
	b = blue;
	a = alpha;
}

bool Color::operator==(const Color& c)
{
	if (r == c.r && g == c.g && b == c.b && a == c.a) return true;
}

Color Color::operator*(const float& m)
{
	return Color(r*m, g*m, b*m, a);
}

Color::~Color()
{
}
