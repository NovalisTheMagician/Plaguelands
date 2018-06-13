#ifndef SDL_WINDOW_HPP_
#define SDL_WINDOW_HPP_

#include "plague.hpp"
#include "window.hpp"

#include <SDL.h>

namespace Plague
{
	class SDLWindow : public Window
	{
	public:
		SDLWindow();
		~SDLWindow();

		bool Init(const WindowInfo &info);
		void Destroy();

		bool HandleEvents();

		void* GetWindowHandle() const;

	private:
		SDL_Window *window;
		void* handle;

	};
}

#endif
