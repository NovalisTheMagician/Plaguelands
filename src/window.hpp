#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "plague.hpp"

namespace Plague
{
	enum WindowType
	{
		WINDOW,
		FULLSCREEN,
		BORDERLESS
	};

	struct WindowInfo
	{
		std::string title;
		uint width;
		uint height;
		WindowType type;
	};

	class Window
	{
	public:
		virtual ~Window() = 0;

		virtual bool Init(const WindowInfo &info) = 0;
		virtual void Destroy() = 0;

		virtual bool HandleEvents() = 0;

	};
}

#endif