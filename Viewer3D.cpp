#include "Viewer3D.h"
#include <glad/glad.h>
#include <array>
#include <glm/glm.hpp>
#include <span>
namespace {
    auto createVertexBuffer(std::span<glm::vec2> vertices)
    {
        GLuint vbo;
        glGenBuffers(1, &vbo);
        GLuint vao;
        glGenVertexArrays(1, &vao);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size_bytes(), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), static_cast<void*>(0)); // position
        glEnableVertexArrayAttrib(vao, 0);

        glBindVertexArray(0);

        return vao;
    }
}



bool Viewer3D::init()
{
    m_engine.init();

    //TODO create vertex data
    std::array<glm::vec2, 3> vertices{
        glm::vec2{ -0.5f,-0.5f },
        glm::vec2{ 0.0f, 0.5f },
        glm::vec2{ 0.5f, -0.5f}
    };
    
    vertexArrayObject = createVertexBuffer(vertices);

    // VertexShader
    // FragmentShader
    // -> ShaderProgram
    return true;
}

void Viewer3D::run()
{
    m_engine.run([this] { draw(); });
}

void Viewer3D::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    // TODO draw triangle

    // bind vertex data
    glBindVertexArray(vertexArrayObject);
    // bind shader program

    //draw 

}
