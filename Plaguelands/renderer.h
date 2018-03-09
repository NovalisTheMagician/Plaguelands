#pragma once

#include <SDL.h>
#include "options.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	bool Init(Options &options);
	void Destroy();

private:
	SDL_GLContext * context;

};
