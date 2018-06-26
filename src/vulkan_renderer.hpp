#ifndef VULKAN_RENDERER_HPP_
#define VULKAN_RENDERER_HPP_

#include "plague.hpp"
#include "renderer.hpp"

namespace Plague
{
	class VulkanRenderer : public Renderer
	{
	public:
		VulkanRenderer();
		~VulkanRenderer();

		bool Init(const RendererInfo &info);
		void Destroy();

		bool LoadTexture(const std::string &textureName);
		bool LoadShader(const std::string &shaderName);
		bool LoadModel(const std::string &modelName);

		// add more

		void DrawScene();

	private:


	};
}

#endif
