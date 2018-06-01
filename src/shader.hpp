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

		virtual GLenum GetShaderType() = 0;
		virtual GLenum GetShaderBit() = 0;

		void SetUniform(std::string location, int value);
		void SetUniform(std::string location, float value);
		void SetUniform(std::string location, glm::ivec2 value);
		void SetUniform(std::string location, glm::vec2 value);
		void SetUniform(std::string location, glm::ivec3 value);
		void SetUniform(std::string location, glm::vec3 value);
		void SetUniform(std::string location, glm::ivec4 value);
		void SetUniform(std::string location, glm::vec4 value);
		void SetUniform(std::string location, glm::mat3 value);
		void SetUniform(std::string location, glm::mat4 value);

	private:
		std::map<std::string, GLuint> uniformLocations;
		GLuint shaderProgram;

	};

	class VertexShader : public Shader
	{
	public:
		GLenum GetShaderType();
		GLenum GetShaderBit();
	};

	class FragmentShader : public Shader
	{
	public:
		GLenum GetShaderType();
		GLenum GetShaderBit();
	};

	class GeometryShader : public Shader
	{
	public:
		GLenum GetShaderType();
		GLenum GetShaderBit();
	};

	class ShaderProgram
	{
	public:
		ShaderProgram(const VertexShader &vertex, const FragmentShader &fragment);
		~ShaderProgram();

		void Use();

	private:
		const VertexShader &vertexShader;
		const FragmentShader &fragmentShader;

	};
}

#endif