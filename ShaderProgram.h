#pragma once
#include <glad/glad.h>

class Shader;

class ShaderProgram
{
public:
	ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
	void bind() const;
private:
	GLuint id{ 0 };
};

