#pragma once
#include <filesystem>
#include <glad/glad.h>

class Shader
{
public:
	Shader(const std::filesystem::path& fileName, GLenum shaderType);

	GLuint get()
	{
		return id;
	}
private:
	GLuint id;
};

