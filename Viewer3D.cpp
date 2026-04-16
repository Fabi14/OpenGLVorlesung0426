#include "Viewer3D.h"
#include <glad/glad.h>
#include <array>
#include <vector>
#include <glm/glm.hpp>
#include <span>
#include "Shader.h"

bool Viewer3D::init()
{
    m_engine.init();

    // create vertex data
    std::array vertices{
        glm::vec2{ -0.5f,-0.5f },
        glm::vec2{ 0.5f, 0.5f },
        glm::vec2{ 0.5f, -0.5f},
        glm::vec2{ -0.5f,0.5f },
    };

    std::vector<unsigned int> indices{ 0, 1, 2, 0, 3, 1 };
    m_oVertexBuffer = VertexBuffer(vertices, indices);

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
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}
