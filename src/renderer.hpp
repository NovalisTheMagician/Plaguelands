#ifndef RENDERER_HPP_
#define RENDERER_HPP_

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

		// add more

		virtual void DrawScene() = 0;

	};
}

#endif
