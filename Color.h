#pragma once
#define RED Color(255,0,0,255)
#define GREEN Color(0,255,0,255)
#define BLUE Color(0,0,255,255)
#define BLACK Color(0,0,0,255)
#define WHITE Color(255,255,255,255)

struct Color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;

	Color();
	Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	bool operator==(const Color& c);
	Color operator*(const float& m);
	~Color();
};

