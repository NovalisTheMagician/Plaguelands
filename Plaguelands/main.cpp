#include <iostream>
#include <SDL.h>

int main(int, char**)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL Error" << SDL_GetError() << std::endl;
	}
	SDL_Quit();
	
	return 0;
}