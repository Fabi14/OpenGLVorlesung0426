#pragma once
#include "UniqueResource.h"
#include <glm/glm.hpp>
#include <span>
#include "Mesh.h"

class VertexBuffer
{
public:
    VertexBuffer(std::span<Vertex> vertices);
    VertexBuffer(std::span<Vertex> vertices, std::span<Index> indices);

    void bind() const;

    size_t getIndexCount() const;

private:
    static GLuint createVao();
    static GLuint createBuffer();
    static void deleteVao(GLuint id);
    static void deleteBuffer(GLuint id);

    UniqueResource m_vao{ createVao(), &deleteVao };
    UniqueResource m_vbo{ createBuffer(), &deleteBuffer };
    UniqueResource m_ebo{ createBuffer(), &deleteBuffer };

    size_t m_indexCount{};
};

