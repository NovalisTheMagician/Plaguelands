#ifndef SHADER_HPP_
#define SHADER_HPP_

#include "Plague.hpp"

#include "glad\glad.h"

#include <glm\glm.hpp>

namespace Plague
{
	class Shader
	{
	public:
		Shader();
		virtual ~Shader() = 0;

		bool Load(const byte *code, std::size_t size);

		virtual GLenum GetShaderType() const = 0;
		virtual GLenum GetShaderBit() const = 0;

		void SetUniform(const std::string &location, int value);
		void SetUniform(const std::string &location, float value);
		void SetUniform(const std::string &location, const glm::ivec2 &value);
		void SetUniform(const std::string &location, const glm::vec2 &value);
		void SetUniform(const std::string &location, const glm::ivec3 &value);
		void SetUniform(const std::string &location, const glm::vec3 &value);
		void SetUniform(const std::string &location, const glm::ivec4 &value);
		void SetUniform(const std::string &location, const glm::vec4 &value);
		void SetUniform(const std::string &location, const glm::mat3 &value);
		void SetUniform(const std::string &location, const glm::mat4 &value);

		GLuint GetProgram() const;

	private:
		GLint GetLocation(const std::string &location);

	private:
		std::map<std::string, GLint> uniformLocations;
		GLuint shaderProgram;

	};

	class VertexShader : public Shader
	{
	public:
		GLenum GetShaderType() const;
		GLenum GetShaderBit() const;
	};

	class FragmentShader : public Shader
	{
	public:
		GLenum GetShaderType() const;
		GLenum GetShaderBit() const;
	};

	class ShaderProgram
	{
	public:
		ShaderProgram();
		~ShaderProgram();

		void SetShaderStage(const Shader &shader);

		void Use();

	private:

		GLuint programPipeline;

	};
}

#endif