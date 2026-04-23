#pragma once
#include "UniqueResource.h"
#include <glm/glm.hpp>
#include <span>

class VertexBuffer
{
public:
    VertexBuffer(std::span<glm::vec2> vertices);
    VertexBuffer(std::span<glm::vec2> vertices, std::span<unsigned int> indices);

    void bind() const;

private:
    static GLuint createVao();
    static GLuint createBuffer();
    static void deleteVao(GLuint id);
    static void deleteBuffer(GLuint id);

    UniqueResource m_vao{ createVao(), &deleteVao };
    UniqueResource m_vbo{ createBuffer(), &deleteBuffer };
    UniqueResource m_ebo{ createBuffer(), &deleteBuffer };
};

