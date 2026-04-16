#include "VertexBuffer.h"
#include <glad/glad.h>

VertexBuffer::VertexBuffer(std::span<glm::vec2> vertices)
{
    glBindVertexArray(*m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, *m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size_bytes(), vertices.data(), GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), static_cast<void*>(0)); // position
    glEnableVertexArrayAttrib(*m_vao, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void VertexBuffer::bind()
{
    glBindVertexArray(*m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, *m_vbo);
}

GLuint VertexBuffer::createVao()
{
    GLuint vao{};
    glGenVertexArrays(1, &vao);
    return vao;
}

GLuint VertexBuffer::createVbo()
{
    GLuint vbo{};
    glGenBuffers(1, &vbo);
    return vbo;
}

void VertexBuffer::deleteVao(GLuint id)
{
    glDeleteVertexArrays(1, &id);
}

void VertexBuffer::deleteVbo(GLuint id)
{
    glDeleteBuffers(1, &id);
}