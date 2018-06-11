#ifndef SHADER_HPP_
#define SHADER_HPP_

#include "Plague.hpp"

#include <glm\glm.hpp>

namespace Plague
{
	class Shader
	{
	public:
		Shader();
		virtual ~Shader() = 0;

	};

	class ShaderProgram
	{
	public:
		ShaderProgram();
		~ShaderProgram();

	};
}

#endif