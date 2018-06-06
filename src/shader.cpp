#include "shader.hpp"

#include <glm\gtc\type_ptr.hpp>

namespace Plague
{
	using std::string;
	using std::size_t;

	using glm::ivec2;
	using glm::vec2;
	using glm::ivec3;
	using glm::vec3;
	using glm::ivec4;
	using glm::vec4;
	using glm::mat3;
	using glm::mat4;

	Shader::Shader()
		: shaderProgram(0)
	{

	}

	Shader::~Shader()
	{
		glDeleteProgram(shaderProgram);
	}

	bool Shader::Load(const byte *code, size_t size)
	{
		shaderProgram = glCreateShaderProgramv(GetShaderType(), 1, reinterpret_cast<const char**>(&code));

		if (shaderProgram > 0)
			return true;

		//check info_log

		return false;
	}

	GLuint Shader::GetProgram() const
	{
		return shaderProgram;
	}

	void Shader::SetUniform(const string &location, int value)
	{
		if (shaderProgram == 0)
			return;
		GLint loc = GetLocation(location);
		if (loc != -1)
			glProgramUniform1i(shaderProgram, loc, value);
	}

	void Shader::SetUniform(const string &location, float value)
	{
		if (shaderProgram == 0)
			return;
		GLint loc = GetLocation(location);
		if (loc != -1)
			glProgramUniform1f(shaderProgram, loc, value);
	}

	void Shader::SetUniform(const string &location, const ivec2 &value)
	{
		if (shaderProgram == 0)
			return;
		GLint loc = GetLocation(location);
		if (loc != -1)
			glProgramUniform2iv(shaderProgram, loc, 1, glm::value_ptr(value));
	}

	void Shader::SetUniform(const string &location, const vec2 &value)
	{
		if (shaderProgram == 0)
			return;
		GLint loc = GetLocation(location);
		if (loc != -1)
			glProgramUniform2fv(shaderProgram, loc, 1, glm::value_ptr(value));
	}

	void Shader::SetUniform(const string &location, const ivec3 &value)
	{
		if (shaderProgram == 0)
			return;
		GLint loc = GetLocation(location);
		if (loc != -1)
			glProgramUniform3iv(shaderProgram, loc, 1, glm::value_ptr(value));
	}

	void Shader::SetUniform(const string &location, const vec3 &value)
	{
		if (shaderProgram == 0)
			return;
		GLint loc = GetLocation(location);
		if (loc != -1)
			glProgramUniform3fv(shaderProgram, loc, 1, glm::value_ptr(value));
	}

	void Shader::SetUniform(const string &location, const ivec4 &value)
	{
		if (shaderProgram == 0)
			return;
		GLint loc = GetLocation(location);
		if (loc != -1)
			glProgramUniform4iv(shaderProgram, loc, 1, glm::value_ptr(value));
	}

	void Shader::SetUniform(const string &location, const vec4 &value)
	{
		if (shaderProgram == 0)
			return;
		GLint loc = GetLocation(location);
		if (loc != -1)
			glProgramUniform4fv(shaderProgram, loc, 1, glm::value_ptr(value));
	}

	void Shader::SetUniform(const string &location, const mat3 &value)
	{
		if (shaderProgram == 0)
			return;
		GLint loc = GetLocation(location);
		if (loc != -1)
			glProgramUniformMatrix3fv(shaderProgram, loc, 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::SetUniform(const string &location, const mat4 &value)
	{
		if (shaderProgram == 0)
			return;
		GLint loc = GetLocation(location);
		if (loc != -1)
			glProgramUniformMatrix4fv(shaderProgram, loc, 1, GL_FALSE, glm::value_ptr(value));
	}

	GLint Shader::GetLocation(const string &location)
	{
		if (uniformLocations.count(location) > 0)
			return uniformLocations[location];
		GLint loc = glGetUniformLocation(shaderProgram, location.c_str());
		if (loc != -1)
			uniformLocations[location] = loc;
		return loc;
	}

	GLenum VertexShader::GetShaderType() const
	{
		return GL_VERTEX_SHADER;
	}

	GLenum VertexShader::GetShaderBit() const
	{
		return GL_VERTEX_SHADER_BIT;
	}

	GLenum FragmentShader::GetShaderType() const
	{
		return GL_FRAGMENT_SHADER;
	}

	GLenum FragmentShader::GetShaderBit() const
	{
		return GL_FRAGMENT_SHADER_BIT;
	}

	ShaderProgram::ShaderProgram()
	{
		glGenProgramPipelines(1, &programPipeline);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgramPipelines(1, &programPipeline);
	}

	void ShaderProgram::SetShaderStage(const Shader &shader)
	{
		glUseProgramStages(programPipeline, shader.GetShaderBit(), shader.GetProgram());
	}

	void ShaderProgram::Use()
	{
		glBindProgramPipeline(programPipeline);
	}
}
