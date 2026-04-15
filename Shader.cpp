#include "Shader.h"

#include <fstream>
#include "DebugOutput.h"

Shader::Shader(const std::filesystem::path& fileName, GLenum shaderType)
{
	id = glCreateShader(shaderType);

	std::ifstream file;
	file.open(fileName);

	std::stringstream codeStream;
	codeStream << file.rdbuf();
	file.close();

	std::string code = codeStream.str();
	auto cStr = code.c_str();

	glShaderSource(id, 1, &cStr, nullptr);
	glCompileShader(id);

	DebugOutput::checkShaderCompilation(*this);
}
