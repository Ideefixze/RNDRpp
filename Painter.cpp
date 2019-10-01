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
	//Sorting by y
	if (A.y>B.y) { std::swap(A, B); }
	if (A.y>C.y) { std::swap(A, C); }
	if (B.y>C.y) { std::swap(B, C); }

	//First triangle A: top vert, B: middle vert, C: bot vert
	//Draw A to B line and stop when y changes.
	//Draw A to C line and stop when y changes.
	//Draw horizontal lines from stop positions.
	//Repeat until A to B is finished.
	//D is where A to C has stopped.
	//Draw A to C line and stop when y changes.
	//Draw B to C line and stop when y changes.
	//Repeat until both finishes.
	//Finish.

	//A to B
	int dx1 = abs(B.x - A.x);
	int sx1 = A.x < B.x ? 1 : -1;
	int dy1 = -abs(B.y - A.y);
	int sy1 = A.y < B.y ? 1 : -1;
	int err1 = dx1 + dy1;
	int x1 = A.x;
	int y1 = A.y;

	//A to C
	int dx2 = abs(C.x - A.x);
	int sx2 = A.x < C.x ? 1 : -1;
	int dy2 = -abs(C.y - A.y);
	int sy2 = A.y < C.y ? 1 : -1;
	int err2 = dx2 + dy2;
	int x2 = A.x;
	int y2 = A.y;

	//B to C
	int dx3 = abs(C.x - B.x);
	int sx3 = B.x < C.x ? 1 : -1;
	int dy3 = -abs(C.y - B.y);
	int sy3 = B.y < C.y ? 1 : -1;
	int err3 = dx3 + dy3;
	int x3 = B.x;
	int y3 = B.y;

	bool AtoB = true;
	bool AtoC = true;
	bool BtoC = false;
	bool transLine1 = false;
	bool transLine2 = false;

	Color AtoBCol;
	Color AtoCCol;
	Color BtoCCol;

	while (AtoC==true)
	{
		transLine1 = false;
		transLine2 = false;

		while (BtoC)
		{
			//BtoCCol = BLUE;
			BtoCCol = ColorInterpolationBetweenVector2(B, C, cB, cC, iVector2(x3, y3));
			//DrawPixel(iVector2(x3, y3), BtoCCol);
			if (x3 == C.x && y3 == C.y)
				BtoC = false;
			int e2 = err3 * 2;
			if (e2 > dy3)
			{
				err3 += dy3;
				x3 += sx3;
			}
			if (e2 < dx3)
			{
				err3 += dx3;
				y3 += sy3;
				//if (x3 == C.x && y3 == C.y)
					//BtoC = false;
				break;
			}
		}
		while (AtoB)
		{
			AtoBCol = ColorInterpolationBetweenVector2(A, B, cA, cB, iVector2(x1, y1));
			//AtoBCol = RED;
			//DrawPixel(iVector2(x1, y1), AtoBCol);
			if (x1 == B.x && y1 == B.y)
			{
				AtoB = false;
				BtoC = true;
				transLine1 = true;
			}
			int e2 = err1 * 2;
			if (e2 > dy1)
			{
				err1 += dy1;
				x1 += sx1;
			}
			if (e2 < dx1)
			{
				err1 += dx1;
				y1 += sy1;
				if (x1 == B.x && y1 == B.y)
				{
					AtoB = false;
					BtoC = true;
					transLine1 = true;
				}
				break;
			}
		}


		while (AtoC && transLine1==false)
		{
			AtoCCol = ColorInterpolationBetweenVector2(A, C, cA, cC, iVector2(x2, y2));
			//AtoCCol = GREEN;
			//DrawPixel(iVector2(x2, y2), WHITE);
			if (x2 == C.x && y2 == C.y)
			{
				AtoC = false;
				//transLine2 = true;
			}
			int e2 = err2 * 2;
			if (e2 > dy2)
			{
				err2 += dy2;
				x2 += sx2;
			}
			if (e2 < dx2)
			{
				err2 += dx2;
				y2 += sy2;
				if (x2 == C.x && y2 == C.y)
				{
					AtoC = false;
					//transLine2 = true;
				}
				break;
			}
		}


		if ((AtoB&&AtoC) || transLine1)
		{
			if (transLine1)
			{
				x1 -= sx1;
				y1 -= sy1;
			}
			//if (y1 != y2)olog("DIFFERENT LEVEL! ATOB");
			DrawLine(iVector2(x1, y2), iVector2(x2, y2), AtoBCol, AtoCCol);
		}
		else if ((AtoC && BtoC) || transLine2)
		{
			//if (y3 != y2)olog("DIFFERENT LEVEL! BTOC");
			if (transLine2)
			{
				x3 -= sx3;
				y3 -= sy3;
			}
			DrawLine(iVector2(x3, y2), iVector2(x2, y2), BtoCCol, AtoCCol);
		}

		/*
		olog("transline ");
		olog(transLine);
		olog("atob ");
		olog(AtoB);
		olog("btoc ");
		olog(BtoC);
		olog("atoc ");
		olog(AtoC);
		olog("-------");

		
		*/
		SDL_Delay(10);
		SDL_RenderPresent(renderer);

	}
	//olog("NICE!");
	//SDL_Delay(10000);
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
		if (e2 > dy)
		{
			err += dy;
			x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
		//SDL_Delay(10);
		SDL_RenderPresent(renderer);
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
	if (cA == cB) return cA;
	float fraction = current.DistanceTo(B) / A.DistanceTo(B);
	return Color((cA.r - cB.r)*fraction + cB.r,
		(cA.g - cB.g)*fraction + cB.g,
		(cA.b - cB.b)*fraction + cB.b,
		(cA.a - cB.a)*fraction + cB.a);
}