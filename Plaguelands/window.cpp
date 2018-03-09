#include "window.h"

Window::Window()
{

}

Window::~Window()
{

}

bool Window::Init(Options &options)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_TIMER) != 0)
	{
		return false;
	}

	std::string title = options.GetString("window_title", "Unicorn-Rainbow-Land");
	int width = options.GetInt("window_width", 800);
	int height = options.GetInt("widnow_height", 600);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (!window)
	{
		SDL_Quit();
		return false;
	}

	return true;
}

void Window::Destroy()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

Renderer *Window::CreateRenderer()
{

}
