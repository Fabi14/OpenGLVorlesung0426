#include "ShaderProgram.h"
#include "Shader.h"

ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader) 
    : id{ glCreateProgram(), [](GLuint id) {glDeleteProgram(id); } }
{
    glAttachShader(*id, vertexShader.get());
    glAttachShader(*id, fragmentShader.get());

    glLinkProgram(*id);

    glDetachShader(*id, vertexShader.get());
    glDetachShader(*id, fragmentShader.get());

    m_modelTransformID = glGetUniformLocation(*id, "model");
    m_viewTransformID = glGetUniformLocation(*id, "viewTransform");
    m_projectionTransformID = glGetUniformLocation(*id, "projectionTransform");
}

void ShaderProgram::bind() const
{
    glUseProgram(*id);
}

void ShaderProgram::setModelTransform(const glm::mat4& transform)
{
    glUniformMatrix4fv(m_modelTransformID, 1, GL_FALSE, &transform[0][0]);
}

void ShaderProgram::setCameraTransform(const glm::mat4& viewTransform, const glm::mat4& projectionTransform)
{
    glUniformMatrix4fv(m_viewTransformID, 1, GL_FALSE, &viewTransform[0][0]);
    glUniformMatrix4fv(m_projectionTransformID, 1, GL_FALSE, &projectionTransform[0][0]);
}
