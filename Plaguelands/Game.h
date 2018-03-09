#pragma once

#include <SDL.h>

class Game
{
public:
	Game();
	~Game();

	bool Init(int, char* []);
	void StartLoop();

private:
	bool CreateWindow();

private:
	SDL_Window *window;
	SDL_GLContext *context;

};
