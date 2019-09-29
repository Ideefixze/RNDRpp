#include "stdafx.h"
#include "Painter.h"

Painter::Painter(SDL_Renderer* rend)
{
	if(rend!=NULL)
	renderer = rend;
}

void Painter::DrawPixel(iVector2 pos, Color col)
{
	SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
	SDL_RenderDrawPoint(renderer, pos.x, pos.y);
	
}



void Painter::DrawLine(iVector2 A, iVector2 B, Color cA, Color cB)
{
	BresenhamLine(A, B, cA, cB);
	/*
	if (abs(B.y - A.y) < abs(B.x - A.y))
	{
		if (A.x > B.x)
			BresenhamLineLow(B, A, cB, cA);
		else
			BresenhamLineLow(A, B, cA, cB);
	}
	else
	{
		if (A.y > B.y)
		{
			BresenhamLineHigh(B, A, cB, cA);
		}
		else
		{
			BresenhamLineHigh(A, B, cA, cB);
		}
	}
	*/
}

void Painter::DrawTriangle(iVector2 A, iVector2 B, iVector2 C, Color cA, Color cB, Color cC)
{
	DrawLine(A, B, cA, cB);
	DrawLine(A, C, cA, cC);
	DrawLine(C, B, cC, cB);
}

void Painter::DrawFilledTriangle(iVector2 A, iVector2 B, iVector2 C, Color cA, Color cB, Color cC)
{
	int dx = abs(B.x - A.x);
	int sx = A.x < B.x ? 1 : -1;
	int dy = -abs(B.y - A.y);
	int sy = A.y < B.y ? 1 : -1;
	int err = dx + dy;
	int x = A.x;
	int y = A.y;

	while (true)
	{
		DrawPixel(iVector2(x, y), ColorInterpolationBetweenVector2(A, B, cA, cB, iVector2(x, y)));
		if (x == B.x && y == B.y)
			break;
		int e2 = err * 2;
		if (e2 >= dy)
		{
			err += dy;
			x += sx;
			DrawLine(iVector2(x, y), C, ColorInterpolationBetweenVector2(A, B, cA, cB, iVector2(x, y)), cC);
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
			DrawLine(iVector2(x, y), C, ColorInterpolationBetweenVector2(A, B, cA, cB, iVector2(x, y)), cC);
		}

		
	}
}

void Painter::BresenhamLine(iVector2 A, iVector2 B, Color cA, Color cB)
{
	int dx = abs(B.x - A.x);
	int sx = A.x < B.x ? 1 : -1;
	int dy =-abs(B.y - A.y);
	int sy = A.y < B.y ? 1 : -1;
	int err = dx + dy;
	int x = A.x;
	int y = A.y;

	while (true)
	{
		DrawPixel(iVector2(x, y), ColorInterpolationBetweenVector2(A,B,cA,cB, iVector2(x, y)));
		if (x == B.x && y == B.y)
			break;
		int e2 = err * 2;
		if (e2 >= dy)
		{
			err += dy;
			x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}

}


void Painter::BresenhamLineLow(iVector2 A, iVector2 B, Color cA, Color cB)
{
	int dx = B.x - A.x;
	int dy = B.y - A.y;
	int yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}

	int x = A.x;
	int y = A.y;
	int p = 2 * dy - dx;

	while (x <= B.x)
	{
		DrawPixel(iVector2(x, y), ColorInterpolationBetweenVector2(A,B,cA,cB,iVector2(x,y)));
		if (p > 0)
		{
			y = y + yi;
			p = p - 2*dx;
		}
		p = p + 2 * dy;

		x += 1;
	}
}
void Painter::BresenhamLineHigh(iVector2 A, iVector2 B, Color cA, Color cB)
{
	int dx = B.x - A.x;
	int dy = B.y - A.y;
	int xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}

	int x = A.x;
	int y = A.y;
	int p = 2 * dx - dy;

	while (y <= B.y)
	{
		DrawPixel(iVector2(x, y), ColorInterpolationBetweenVector2(A, B, cA, cB, iVector2(x, y)));
		if (p > 0)
		{
			x = x + xi;
			p = p - 2*dy;
		}
		p = p + 2 * dx;

		y = y + 1;
	}
}

Color Painter::ColorInterpolationBetweenVector2(iVector2 A, iVector2 B, Color cA, Color cB, iVector2 current)
{
	float fraction = current.DistanceTo(B) / A.DistanceTo(B);
	return Color((cA.r - cB.r)*fraction + cB.r,
		(cA.g - cB.g)*fraction + cB.g,
		(cA.b - cB.b)*fraction + cB.b,
		(cA.a - cB.a)*fraction + cB.a);
}