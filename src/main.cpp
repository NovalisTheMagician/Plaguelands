#include "plague.hpp"

#include <SDL.h>
#include <SDL_vulkan.h>

#include "sdl_window.hpp"

#include "texture.hpp"
#include "filesystem.hpp"

#include "shader.hpp"

#include <Windows.h>

Plague::Texture diffuse;
Plague::Filesystem filesystem("..\\..\\", true);

Plague::ShaderProgram *testShader;

Plague::SDLWindow window;

using std::vector;
using std::string;

void Init()
{
	Plague::WindowInfo windowInfo;
	windowInfo.title = "Plaguelands";
	windowInfo.width = 800;
	windowInfo.height = 600;
	windowInfo.type = Plague::WindowType::WINDOW;

	window.Init(windowInfo);

	filesystem.AddModDirectory("Assets");

	std::size_t size;
	const byte* vertData = filesystem.ReadFile("shader/testShader.vert", &size);
	if (vertData != nullptr)
	{
		delete[] vertData;
	}

	const byte* fragData = filesystem.ReadFile("shader/testShader.frag", &size);
	if (vertData != nullptr)
	{
		delete[] fragData;
	}

	testShader = new Plague::ShaderProgram();

	uint pixels[4] = 
	{
		0xFF0000FF, 0x00FF00FF,
		0x0000FFFF, 0xFFFFFFFF
	};
	diffuse.Load(reinterpret_cast<byte*>(&pixels), sizeof pixels);
}

void Update()
{

}

void Draw()
{

}

void Destroy()
{
	delete testShader;
}

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
	{
		return -1;
	}

#ifdef _DEBUG
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE | SDL_GL_CONTEXT_DEBUG_FLAG);
#else
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif

	SDL_Window *window = SDL_CreateWindow("Plaguelands", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_VULKAN);

	Init();

	bool isRunning = true;

	unsigned int currentTime = SDL_GetTicks();
	unsigned int pastTime = currentTime;

	float targetDelta = 1.0f / 60.0f;
	float accum = 0;

	while (isRunning)
	{
		SDL_Event ev;
		if (SDL_PollEvent(&ev) > 0)
		{
			if (ev.type == SDL_QUIT)
				isRunning = false;

			if (ev.type == SDL_KEYDOWN)
			{
				switch (ev.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					isRunning = false;
					break;
				}
			}
		}

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

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}