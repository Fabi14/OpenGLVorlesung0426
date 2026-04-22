#include "Viewer3D.h"
#include <glad/glad.h>
#include <array>
#include <vector>
#include <glm/glm.hpp>
#include <span>
#include "Shader.h"
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtx/transform.hpp>

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
    m_engine.run([this](double deltaTime) { update(deltaTime); });
}

void Viewer3D::update(double deltaTime)
{

    angle += 0.2f;
    auto rotation = glm::rotate(glm::radians(angle), glm::vec3{ 0.f,0.f,1.f });
    auto translation = glm::translate(glm::vec3{1.f,0.f,-1.f });
    auto modelMatrix = rotation * glm::scale(glm::vec3{ 0.2f,0.2f,1.f }) * translation;


    glClear(GL_COLOR_BUFFER_BIT);
    // draw
    if (m_oVertexBuffer && m_oShaderProgram)
    {
        m_oVertexBuffer->bind();
        m_oShaderProgram->bind();
        m_oShaderProgram->setModelTransform(modelMatrix);
        m_oShaderProgram->setCameraTransform(m_camera.getViewTransform(), m_camera.getProjectionTransform());

        //draw 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

void Viewer3D::handleInput(double deltaTime)
{
    // TODO move camera with WASD
    //if (m_engine.getKey())
    //{
    //    m_camera.position += 
    //}
}
