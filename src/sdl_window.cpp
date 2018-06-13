#include "sdl_window.hpp"

#include <SDL_syswm.h>

namespace Plague
{
	SDLWindow::SDLWindow()
		: window(nullptr), handle(nullptr)
	{

	}

	SDLWindow::~SDLWindow()
	{

	}

	bool SDLWindow::Init(const WindowInfo &info)
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
		{
			return false;
		}

		window = SDL_CreateWindow(info.title.c_str(), 
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			info.width, info.height, SDL_WINDOW_VULKAN);

		if (!window)
		{
			return false;
		}

		SDL_SysWMinfo wminfo;
		SDL_VERSION(&wminfo.version);
		SDL_GetWindowWMInfo(window, &wminfo);
		handle = static_cast<void*>(wminfo.info.win.window);

		return true;
	}

	void SDLWindow::Destroy()
	{
		if (window)
		{
			SDL_DestroyWindow(window);
			window = nullptr;
		}
		SDL_Quit();
	}

	bool SDLWindow::HandleEvents()
	{
		SDL_Event ev;
		while (SDL_PollEvent(&ev) > 0)
		{
			if (ev.type == SDL_QUIT)
				return false;
		}

		return true;
	}

	void* SDLWindow::GetWindowHandle() const
	{
		return handle;
	}
}
