#pragma once
#include <SDL.h>
#include "Painter.h"
#include "utils.h"
#include "VecMath.h"
class Engine
{
	int width, height;
	bool run;
	SDL_Window* window=NULL;
	SDL_Surface* mainSurface=NULL;
	SDL_Renderer* renderer = NULL;
	Painter* painter = NULL;

	float rotateX=0.0f;
	float rotateY=0.0f;
	float rotateZ=0.0f;
public:
	Engine();
	~Engine();
	
	//Handles input and other events.
	void HandleInput(); 

	//Main renderer loop.
	bool Loop();

	bool Draw();

};

