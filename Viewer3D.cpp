#include "Viewer3D.h"
#include <glad/glad.h>
#include <array>
#include <glm/glm.hpp>
#include <span>
#include "Shader.h"

bool Viewer3D::init()
{
    m_engine.init();

    // create vertex data
    std::array<glm::vec2, 3> vertices{
        glm::vec2{ -0.5f,-0.5f },
        glm::vec2{ 0.0f, 0.5f },
        glm::vec2{ 0.5f, -0.5f}
    };
    m_oVertexBuffer = VertexBuffer(vertices);

    // VertexShader
    Shader vertexShader("VertexShader.glsl", GL_VERTEX_SHADER);
    // FragmentShader
    Shader fragmentShader("FragmentShader.glsl", GL_FRAGMENT_SHADER);
    // -> ShaderProgram
    m_oShaderProgram = ShaderProgram(vertexShader, fragmentShader);

    return true;
}

void Viewer3D::run()
{
    m_engine.run([this] { draw(); });
}

void Viewer3D::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    // draw triangle
    if (m_oVertexBuffer && m_oShaderProgram)
    {
        m_oVertexBuffer->bind();
        m_oShaderProgram->bind();
        //draw 
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}
