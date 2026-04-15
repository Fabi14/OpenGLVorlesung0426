#pragma once
#include <glad/glad.h>
#include <utility>
#include "UniqueResource.h"

class Shader;

class ShaderProgram
{
public:
	ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
	void bind() const;
private:
	UniqueResource id;
};

