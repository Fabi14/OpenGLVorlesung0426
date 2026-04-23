#include "ShaderProgram.h"
#include "Shader.h"

ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader) 
    : m_id{ glCreateProgram(), [](GLuint id) {glDeleteProgram(id); } }
{
    glAttachShader(*m_id, vertexShader.get());
    glAttachShader(*m_id, fragmentShader.get());

    glLinkProgram(*m_id);

    glDetachShader(*m_id, vertexShader.get());
    glDetachShader(*m_id, fragmentShader.get());

    m_modelTransformID = glGetUniformLocation(*m_id, "model");
    m_viewTransformID = glGetUniformLocation(*m_id, "viewTransform");
    m_projectionTransformID = glGetUniformLocation(*m_id, "projectionTransform");

    m_winSizeID = glGetUniformLocation(*m_id, "winSize");
}

void ShaderProgram::bind() const
{
    glUseProgram(*m_id);
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

void ShaderProgram::setWinSize(glm::vec2 size)
{
    //glUniform2fv(m_winSizeID, 2, &size[0]);

    glUniform2f(m_winSizeID, size.x,size.y);
}
