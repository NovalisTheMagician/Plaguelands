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
	{
	}

	Texture::~Texture()
	{
	}

	bool Texture::Load(const byte *data, size_t size)
	{
		int width, height, numChannels;
		byte *image = stbi_load_from_memory(data, size, &width, &height, &numChannels, 4);
		if (!image)
		{
			return true;
		}
		return false;
	}
}
