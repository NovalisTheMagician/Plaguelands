#pragma once

#include <SDL.h>
#include "options.h"
#include "renderer.h"

class Window
{
public:
	Window();
	~Window();

	bool Init(Options &options);
	void Destroy();
	Renderer *CreateRenderer();

private:
	SDL_Window * window;

};
