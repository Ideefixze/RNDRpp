#pragma once
#include "Color.h"
#include "iVector2.h"
#include <SDL.h>
#include "utils.h"
#include <algorithm> 
class Painter
{
	SDL_Renderer* renderer=NULL;
	void BresenhamLineLow(iVector2 A, iVector2 B, Color cA, Color cB);
	void BresenhamLineHigh(iVector2 A, iVector2 B, Color cA, Color cB);
	void BresenhamLine(iVector2 A, iVector2 B, Color cA, Color cB);
public:
	Painter(SDL_Renderer* rend);
	void DrawPixel(iVector2 pos, Color col);
	void DrawLine(iVector2 A, iVector2 B, Color cA, Color cB);
	void DrawTriangle(iVector2 A, iVector2 B, iVector2 C, Color cA, Color cB, Color cC);
	void DrawFilledTriangle(iVector2 A, iVector2 B, iVector2 C, Color cA, Color cB, Color cC);
	Color ColorInterpolationBetweenVector2(iVector2 A, iVector2 B, Color cA, Color cB, iVector2 current);
};

