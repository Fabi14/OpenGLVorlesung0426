#pragma once
#include <filesystem>
#include "UniqueResource.h"

class Shader
{
public:
	Shader(const std::filesystem::path& fileName, GLenum shaderType);

	GLuint get() const
	{
		return *m_id;
	}
private:
	UniqueResource m_id;
};

