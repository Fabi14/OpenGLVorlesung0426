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
}

void ShaderProgram::bind() const
{
    glUseProgram(*id);
}
