#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Plague
{
	using std::string;
	using std::size_t;

	uint Texture::defaultTexture[4] = 
	{
		0xFFFFFFFF, 0xFF00FFFF,
		0xFF00FFFF, 0xFFFFFFFF
	};

	Texture::Texture()
		: textureID(0)
	{
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &textureID);
	}

	bool Texture::Load(const byte *data, size_t size)
	{
		int width, height, numChannels;
		byte *image = stbi_load_from_memory(data, size, &width, &height, &numChannels, 4);
		if (!image)
		{
			if (textureID != 0)
				glGenTextures(1, &textureID);

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

			return true;
		}
		return false;
	}

	GLuint Texture::GetTextureID()
	{
		if (textureID == 0)
		{
			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, defaultTexture);
		}
		return textureID;
	}

	void Texture::Bind(GLenum textureUnit)
	{
		glActiveTexture(textureUnit);
		glBindTexture(GL_TEXTURE_2D, GetTextureID());
	}
}
