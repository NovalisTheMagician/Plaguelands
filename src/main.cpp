#include "plague.hpp"

#include <SDL.h>
#include <SDL_vulkan.h>

#include "sdl_window.hpp"
#include "lua_scriptengine.hpp"

Plague::SDLWindow window;
Plague::LuaScriptEngine scriptEngine;

using std::vector;
using std::string;

void Init()
{
	Plague::WindowInfo windowInfo = {
		"Plaguelands",
		800, 600,
		Plague::WindowType::WINDOW
	};
	window.Init(windowInfo);

	Plague::ScriptEngineInfo scriptInfo = {
		"../../assets/scripts/"
	};
	scriptEngine.Init(scriptInfo);
}

void Update()
{
	window.HandleEvents();
}

void Draw()
{

}

void Destroy()
{
	window.Destroy();
}

int main(int argc, char *argv[])
{
#ifdef _DEBUG
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE | SDL_GL_CONTEXT_DEBUG_FLAG);
#else
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif

	Init();

	bool isRunning = true;

	unsigned int currentTime = SDL_GetTicks();
	unsigned int pastTime = currentTime;

	float targetDelta = 1.0f / 60.0f;
	float accum = 0;

	while (isRunning)
	{
		currentTime = SDL_GetTicks();
		float delta = (currentTime - pastTime) / 1000.0f;
		pastTime = currentTime;

		accum += delta;
		while (accum >= targetDelta)
		{
			Update();
			accum -= targetDelta;
		}

		Draw();
	}

	Destroy();

	return 0;
}