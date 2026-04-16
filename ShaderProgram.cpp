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
}

void ShaderProgram::bind() const
{
    glUseProgram(*id);
}

void ShaderProgram::setModelTransform(const glm::mat4& transform)
{
    glUniformMatrix4fv(m_modelTransformID, 1, GL_FALSE, &transform[0][0]);
}
