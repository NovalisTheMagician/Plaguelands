#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include "plague.hpp"

namespace Plague
{
	struct RendererInfo
	{
		void* windowHandle;
	};

	class Renderer
	{
	public:
		virtual ~Renderer() = 0;

		virtual bool Init(const RendererInfo &info) = 0;
		virtual void Destroy() = 0;

		virtual bool LoadTexture(const std::string &textureName) = 0;
		virtual bool LoadShader(const std::string &shaderName) = 0;
		virtual bool LoadModel(const std::string &modelName) = 0;

		// add more

		virtual void DrawScene() = 0;

	};
}

#endif
