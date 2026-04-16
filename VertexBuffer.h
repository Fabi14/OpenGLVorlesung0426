#pragma once
#include "UniqueResource.h"
#include <glm/glm.hpp>
#include <span>

class VertexBuffer
{
public:
    VertexBuffer(std::span<glm::vec2> vertices);

    void bind();

private:
    static GLuint createVao();
    static GLuint createVbo();
    static void deleteVao(GLuint id);
    static void deleteVbo(GLuint id);

    UniqueResource m_vao{ createVao(), &deleteVao };
    UniqueResource m_vbo{ createVbo(), &deleteVbo };
};

