#pragma once
#include <glad/glad.h>
#include <utility>
#include "UniqueResource.h"
#include <glm/glm.hpp>

class Shader;

class ShaderProgram
{
public:
	ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
	void bind() const;

	void setModelTransform(const glm::mat4& transform);
private:
	UniqueResource id;
	GLuint m_modelTransformID{};
};

