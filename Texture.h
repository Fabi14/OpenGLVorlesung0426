#pragma once
#include <filesystem>
#include "UniqueResource.h"

class ShaderProgram;

class Texture
{
public:
	Texture(const std::string& path);
	void bind(const ShaderProgram& shaderProgram, const std::string& uniformName, int textureUnit);

private:
	UniqueResource m_id{
		[] {GLuint id; glGenTextures(1,&id); return id; }(),
		[](GLuint id) {glDeleteTextures(1,&id); } 
	};
};

