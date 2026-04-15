#pragma once
#include <glad/glad.h>
#include <utility>

class Shader;

class ShaderProgram
{
public:
	ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
	ShaderProgram(const ShaderProgram&) = delete;
	const ShaderProgram& operator=(const ShaderProgram&) = delete;
	ShaderProgram(ShaderProgram&& old) noexcept : id{ std::exchange(old.id, 0) }
	{}
	const ShaderProgram& operator=(ShaderProgram&& old)noexcept
	{
		std::swap(*this, old);
		return *this;
	}

	~ShaderProgram()
	{
		glDeleteProgram(id);
	}
	void bind() const;
private:
	GLuint id{ 0 };
};

