#include "texture.hpp"

#include <gli\load.hpp>
#include <gli\gl.hpp>

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

	bool Texture::Load(const string &path)
	{
		gli::texture texture(gli::load(path));
		if (texture.empty())
			return false;

		return Load(texture);
	}

	bool Texture::Load(const char *data, size_t size)
	{
		gli::texture texture(gli::load(data, size));
		if (texture.empty())
			return false;

		return Load(texture);
	}

	bool Texture::Load(gli::texture texture)
	{
		gli::gl gl(gli::gl::PROFILE_KTX);
		gli::gl::format const format = gl.translate(texture.format(), texture.swizzles());
		GLenum target = gl.translate(texture.target());
		if (target != gli::TARGET_2D)
			return false;

		glGenTextures(1, &textureID);
		glBindTexture(target, textureID);
		glTexParameteri(target, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(texture.levels() - 1));
		glTexParameteriv(target, GL_TEXTURE_SWIZZLE_RGBA, &format.Swizzles[0]);
		glTexStorage2D(target, static_cast<GLint>(texture.levels()), format.Internal, texture.extent(0).x, texture.extent(0).y);
		for (size_t level = 0; level < texture.levels(); ++level)
		{
			glm::tvec3<GLsizei> extent(texture.extent(level));
			if (gli::is_compressed(texture.format))
				glCompressedTexSubImage2D(
					target, static_cast<GLint>(level), 0, 0, extent.x, extent.y,
					format.External, static_cast<GLsizei>(texture.size(level)), texture.data(0, 0, level));
			else
				glTexSubImage2D(
					target, static_cast<GLint>(level), 0, 0, extent.x, extent.y,
					format.External, format.Type, texture.data(0, 0, level));
		}

		return true;
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
