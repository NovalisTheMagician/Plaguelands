#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include "plague.hpp"

namespace Plague
{
	class Texture
	{
	public:
		Texture();
		~Texture();

		bool Load(const byte *data, std::size_t size);

	private:
		static uint defaultTexture[4];

	};
}

#endif
