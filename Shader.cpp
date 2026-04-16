#include "Shader.h"
#include <glad/glad.h>
#include <fstream>
#include "DebugOutput.h"

Shader::Shader(const std::filesystem::path& fileName, GLenum shaderType)
	: m_id{ glCreateShader(shaderType) , [](GLuint id) { glDeleteShader(id); } }
{
	std::ifstream file;
	file.open(fileName);

	std::stringstream codeStream;
	codeStream << file.rdbuf();
	file.close();

	std::string code = codeStream.str();
	auto cStr = code.c_str();

	glShaderSource(*m_id, 1, &cStr, nullptr);
	glCompileShader(*m_id);

	DebugOutput::checkShaderCompilation(*this);
}
