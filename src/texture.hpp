#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include "plague.hpp"

#include <GL\glew.h>

namespace Plague
{
	class Texture
	{
	public:
		Texture();
		~Texture();

		bool Load(const byte *data, std::size_t size);

		GLuint GetTextureID();

		void Bind(GLenum textureUnit);

	private:
		GLuint textureID;
		static uint defaultTexture[4];

	};
}

#endif
