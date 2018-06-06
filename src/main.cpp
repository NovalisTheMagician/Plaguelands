#include "plague.hpp"

#include "glad/glad.h"

#include <SDL.h>

#include "texture.hpp"
#include "filesystem.hpp"

#include "shader.hpp"

#include <Windows.h>

Plague::Texture diffuse;
Plague::Filesystem filesystem("..\\..\\", true);

Plague::VertexShader testVertexShader;
Plague::FragmentShader testFragmentShader;
Plague::ShaderProgram *testShader;

using std::vector;
using std::string;

void Init()
{
	filesystem.AddModDirectory("Assets");

	std::size_t size;
	const byte* vertData = filesystem.ReadFile("shader/testShader.vert", &size);
	if (vertData != nullptr)
	{
		testVertexShader.Load(vertData, size);
		delete[] vertData;
	}

	const byte* fragData = filesystem.ReadFile("shader/testShader.frag", &size);
	if (vertData != nullptr)
	{
		testFragmentShader.Load(fragData, size);
		delete[] fragData;
	}

	testShader = new Plague::ShaderProgram();
	testShader->SetShaderStage(testVertexShader);
	testShader->SetShaderStage(testFragmentShader);

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

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_Window *window = SDL_CreateWindow("Plaguelands", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (!context)
	{
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	SDL_GL_MakeCurrent(window, context);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		//hmmm
	}

	Init();

	glViewport(0, 0, 800, 600);

	bool isRunning = true;

	unsigned int currentTime = SDL_GetTicks();
	unsigned int pastTime = currentTime;

	float targetDelta = 1.0f / 60.0f;
	float accum = 0;

	glClearColor(0, 1, 0, 1);
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

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		Draw();

		SDL_GL_SwapWindow(window);
	}

	Destroy();

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}