#include "stdafx.h"
#include "Engine.h"



Engine::Engine()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	width = 400;
	height = 400;
	window = SDL_CreateWindow("Renderer", 500, 300, width*2, height*2, SDL_WINDOW_OPENGL);
	run = true;

	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_RenderSetScale(renderer, 2, 2);
	painter = new Painter(renderer);
	
}


Engine::~Engine()
{
}


void Engine::HandleInput()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			run = false;
			break;
		}
		break;

	case SDL_MOUSEBUTTONDOWN:
		// Handle mouse clicks here.
		break;

	case SDL_QUIT:
		run = false;
		break;

	default:
		break;
	}
}

bool Engine::Loop()
{
	while (run)
	{
		HandleInput();
		Draw();
	}

	SDL_FreeSurface(mainSurface);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return true;
}


bool Engine::Draw()
{
	SDL_SetRenderDrawColor(renderer, 0, 32, 128, 255);
	SDL_RenderClear(renderer);

	//painter->DrawPixel(iVector2(10, 10), RED);
	//painter->DrawPixel(iVector2(30, 40), GREEN);
	float ti = SDL_GetTicks() / 16.0f;
	//painter->DrawPixel(iVector2(40, 40), BLACK);
	//painter->DrawLine(iVector2(40, 40), iVector2(25*cosf(t)+40, 25*sinf(t)+40), RED, GREEN);
	int ticks = SDL_GetTicks();

	//painter->DrawFilledTriangle(iVector2(10 * cosf(t) + 50, 10 * sinf(t)+50), iVector2(30 * cosf(t) + 60, 30 * sinf(t) + 60), iVector2(30, 50), RED, BLUE, WHITE);
	Vector3 tri[3] = { Vector3(0.0f,0.0f,0.0f), Vector3(1.0f,1.0f,0.0f), Vector3(1.0f,0.0f,0.0f)};
	Vector3 tri2[3] = { Vector3(0.0f,0.0f,0.0f), Vector3(0.0f,1.0f,0.0f), Vector3(1.0f,1.0f,0.0f)};
	Vector3 tri3[3] = { Vector3(0.0f,0.0f,1.0f), Vector3(0.0f,1.0f,1.0f), Vector3(0.0f,1.0f,0.0f) };
	Vector3 tri4[3] = { Vector3(0.0f,0.0f,1.0f), Vector3(1.0f,0.0f,1.0f), Vector3(1.0f,1.0f,1.0f) };
	Triangle tr (tri);
	Triangle tr2 (tri2);
	Triangle tr3(tri3);
	Triangle tr4(tri4);
	Mesh m;
	m.triangles.push_back(tr);
	m.triangles.push_back(tr2);
	//m.triangles.push_back(tr3);
	//m.triangles.push_back(tr4);

	for (auto t : m.triangles)
	{
		t.verts[0] = RotatePointX(t.verts[0], ti);
		t.verts[1] = RotatePointX(t.verts[1], ti);
		t.verts[2] = RotatePointX(t.verts[2], ti);

	    t.verts[0] = RotatePointZ(t.verts[0], ti);
		t.verts[1] = RotatePointZ(t.verts[1], ti);
		t.verts[2] = RotatePointZ(t.verts[2], ti);

		float dis = 4.0f;
		t.verts[0].z += dis;
		t.verts[1].z += dis;
		t.verts[2].z += dis;

		float angle = 90.0f;
		float aspect = (float)width / (float)height;
		Vector2 a = ProjectedPoint(t.verts[0], angle, aspect);
		Vector2 b = ProjectedPoint(t.verts[1], angle, aspect);
		Vector2 c = ProjectedPoint(t.verts[2], angle, aspect);
		
		a.x += 1.0f; a.y += 1.0f;
		b.x += 1.0f; b.y += 1.0f;
		c.x += 1.0f; c.y += 1.0f;

		a.x *= 0.5f * (float)width; a.y *= 0.5f * (float)height;
		b.x *= 0.5f * (float)width; b.y *= 0.5f * (float)height;
		c.x *= 0.5f * (float)width; c.y *= 0.5f * (float)height;
		
		painter->DrawFilledTriangle(iVector2((int)a.x, (int)a.y), iVector2((int)b.x, (int)b.y), iVector2((int)c.x, (int)c.y), RED, GREEN, BLUE);
		log("a: ");
		log(a.x);
		log(a.y);
		log("b: ");
		log(b.x);
		log(b.y);
		log("c: ");
		log(c.x);
		log(c.y);
	}

	
	int ticks2 = SDL_GetTicks();
	log(ticks2 - ticks);
	//SDL_Delay(2000);
	//painter->DrawPixel(iVector2(25 * cosf(t) + 40, 25 * sinf(t) + 40), BLACK);
	SDL_RenderPresent(renderer);

	return true;
}