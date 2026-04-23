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
	void setCameraTransform(const glm::mat4& viewTransform, const glm::mat4& projectionTransform);

	void setWinSize(glm::vec2 size);
private:
	UniqueResource m_id;
	GLuint m_modelTransformID{};
	GLuint m_viewTransformID{};
	GLuint m_projectionTransformID{};
	GLuint m_winSizeID{};
};

