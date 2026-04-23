#include "VertexBuffer.h"
#include <glad/glad.h>

VertexBuffer::VertexBuffer(std::span<Vertex> vertices)
{
    glBindVertexArray(*m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, *m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size_bytes(), vertices.data(), GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position))); // position
    glEnableVertexArrayAttrib(*m_vao, 0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex,normal))); // normal
    glEnableVertexArrayAttrib(*m_vao, 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

VertexBuffer::VertexBuffer(std::span<Vertex> vertices, std::span<Index> indices) 
 : VertexBuffer(vertices)
{
    m_indexCount = indices.size();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size_bytes(), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexBuffer::bind() const
{
    glBindVertexArray(*m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, *m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_ebo);
}

size_t VertexBuffer::getIndexCount() const
{
    return m_indexCount;
}

GLuint VertexBuffer::createVao()
{
    GLuint vao{};
    glGenVertexArrays(1, &vao);
    return vao;
}

GLuint VertexBuffer::createBuffer()
{
    GLuint vbo{};
    glGenBuffers(1, &vbo);
    return vbo;
}

void VertexBuffer::deleteVao(GLuint id)
{
    glDeleteVertexArrays(1, &id);
}

void VertexBuffer::deleteBuffer(GLuint id)
{
    glDeleteBuffers(1, &id);
}