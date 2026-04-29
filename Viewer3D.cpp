#include "Viewer3D.h"
#include <glad/glad.h>
#include <array>
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <span>
#include "Shader.h"
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtx/transform.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Mesh.h"

bool Viewer3D::init()
{
    m_engine.init();

    // create vertex data
    auto quad = Mesh::getQuad();
    m_oVertexBuffer = VertexBuffer(quad.vertices, quad.indices);

    auto cube = Mesh::getCube();
    m_oVertexBufferCube = VertexBuffer(cube.vertices, cube.indices);

    // VertexShader
    Shader vertexShader("VertexShader.glsl", GL_VERTEX_SHADER);
    // FragmentShader
    Shader fragmentShader("FragmentShader.glsl", GL_FRAGMENT_SHADER);
    // -> ShaderProgram
    m_oShaderProgram = ShaderProgram(vertexShader, fragmentShader);

    Shader fragmentShaderPhong("FragmentShader_Phong.glsl", GL_FRAGMENT_SHADER);
    m_oShaderProgramCube = ShaderProgram(vertexShader, fragmentShaderPhong);

    return true;
}

void Viewer3D::run()
{
    m_engine.run([this](double deltaTime) { update(deltaTime); });
}

void Viewer3D::update(double deltaTime)
{
    handleInput(deltaTime);
    createGui();

    glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
    m_angleForModelTransform += m_rotationSpeed * static_cast<float>(deltaTime);
    auto rotation = glm::rotate(glm::radians(m_angleForModelTransform), glm::vec3{ 0.f,0.f,1.f });
    auto translation = glm::translate(glm::vec3{1.f,0.f,-1.f });
    auto modelMatrix = rotation * glm::scale(glm::vec3{ 0.2f,0.2f,1.f }) * translation;
    auto modelMatrix2 = glm::scale(glm::vec3{ 0.2f,0.2f,1.f }) * glm::translate(glm::vec3{ 0.f,0.f,-1.f });

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_oVertexBufferCube && m_oShaderProgramCube)
    {
        m_oVertexBufferCube->bind();
        m_oShaderProgramCube->bind();
        m_oShaderProgramCube->setWinSize(m_engine.getWindowSize());
        m_oShaderProgramCube->setCameraTransform(m_camera.getViewTransform(), m_camera.getProjectionTransform(m_engine.getWindowAspectRatio()), m_camera.position);
        m_oShaderProgramCube->setModelTransform(glm::identity<glm::mat4>());
        glDrawElements(GL_TRIANGLES, m_oVertexBufferCube->getIndexCount(), GL_UNSIGNED_INT, 0);
    }


    // draw Square
    if ( m_oVertexBuffer && m_oShaderProgram)
    {
        m_oVertexBuffer->bind();
        m_oShaderProgram->bind();
        m_oShaderProgram->setWinSize(m_engine.getWindowSize());
        m_oShaderProgram->setCameraTransform(
            m_camera.getViewTransform(), 
            m_camera.getProjectionTransform(m_engine.getWindowAspectRatio()),
            m_camera.position);

        //draw 
        if (m_drawSquare)
        {
            m_oShaderProgram->setModelTransform(modelMatrix);
            glDrawElements(GL_TRIANGLES, m_oVertexBuffer->getIndexCount(), GL_UNSIGNED_INT, 0);
        }
        if (m_drawSquare2)
        {
            m_oShaderProgram->setModelTransform(modelMatrix2);
            glDrawElements(GL_TRIANGLES, m_oVertexBuffer->getIndexCount(), GL_UNSIGNED_INT, 0);
        }
    }
    
}

void Viewer3D::handleInput(double deltaTime)
{
    if (m_engine.getKey(GLFW_KEY_SPACE))
    {
        m_bShowImguiWindow = true;
    }

    auto tempDir = m_camera.getDirection();
    const float speed{ 5.f };
    const float time = static_cast<float>(deltaTime);
    // TODO move camera with WASD
    if (m_engine.getKey(GLFW_KEY_W))
    {
        m_camera.position += tempDir * time * speed;
    }
    if (m_engine.getKey(GLFW_KEY_S))
    {
        m_camera.position += -tempDir * time * speed;
    }
    if (m_engine.getKey(GLFW_KEY_A))
    {
        m_camera.position += -glm::cross(tempDir, m_camera.up) * time * speed;
    }
    if (m_engine.getKey(GLFW_KEY_D))
    {
        m_camera.position += glm::cross(tempDir, m_camera.up) * time * speed;
    }

    glm::vec2 newMousePos = m_engine.getMousePos();

    float xOffset{ newMousePos.x - m_lastMousePos.x };
    float yOffset{ newMousePos.y - m_lastMousePos.y };

    m_lastMousePos = newMousePos;

    float angularSpeed = 10.f;
    if (m_engine.getMouseButton(1))
    {
        m_camera.pitch -= yOffset * time * angularSpeed;
        m_camera.yaw -= xOffset * time * angularSpeed;

        m_camera.pitch = glm::clamp(m_camera.pitch, -89.f, 89.f);
    }
}

void Viewer3D::createGui()
{
    static float f = 0.0f;
    static int counter = 0;

    if (m_bShowImguiWindow)
    {
        ImGui::Begin("Hello, world!", &m_bShowImguiWindow);// Create a window called "Hello, world!" and append into it.

        ImGui::Checkbox("draw square", &m_drawSquare);
        ImGui::Checkbox("draw square 2", &m_drawSquare2);
        ImGui::Text("Background");
        ImGui::ColorEdit3("clear color", (float*)&m_clearColor); // Edit 3 floats representing a color
        ImGui::DragFloat("Rotation speed [°/s]",&m_rotationSpeed,10.f,0.f,720.f,"%.0f");

        ImGui::DragFloat3("Camera Position", &m_camera.position[0]);
        ImGui::End();
    }
}