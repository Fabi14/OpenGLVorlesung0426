#pragma once
#include <filesystem>
#include <glad/glad.h>

class Shader
{
public:
	Shader(const std::filesystem::path& fileName, GLenum shaderType);

	GLuint get() const
	{
		return id;
	}
private:
	GLuint id;
};

