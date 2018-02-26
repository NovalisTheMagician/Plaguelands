#include <iostream>
#include <SDL.h>

#define GLEW_STATIC
#include <GL\glew.h>

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL Error" << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
	if (!win)
	{
		std::cout << "SDL Error" << SDL_GetError() << std::endl;
		SDL_Quit();
		return 2;
	}

	SDL_GLContext context = SDL_GL_CreateContext(win);
	SDL_GL_MakeCurrent(win, context);

	glewExperimental = true;
	glewInit();

	SDL_Event ev;
	while (true)
	{
		if (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT) break;
		}

		glClearColor(0, 1, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		SDL_GL_SwapWindow(win);
	}

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);
	SDL_Quit();
	
	return 0;
}