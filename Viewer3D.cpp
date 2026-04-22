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
    handleInput(deltaTime);
    createGui();

    glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
    angle += m_rotationSpeed * static_cast<float>(deltaTime);
    auto rotation = glm::rotate(glm::radians(angle), glm::vec3{ 0.f,0.f,1.f });
    auto translation = glm::translate(glm::vec3{1.f,0.f,-1.f });
    auto modelMatrix = rotation * glm::scale(glm::vec3{ 0.2f,0.2f,1.f }) * translation;


    glClear(GL_COLOR_BUFFER_BIT);

    // draw Square
    if (m_drawSquare && m_oVertexBuffer && m_oShaderProgram)
    {
        m_oVertexBuffer->bind();
        m_oShaderProgram->bind();
        m_oShaderProgram->setModelTransform(modelMatrix);
        m_oShaderProgram->setCameraTransform(m_camera.getViewTransform(), m_camera.getProjectionTransform(m_engine.getWindowAspectRatio()));

        //draw 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

void Viewer3D::handleInput(double deltaTime)
{
    if (m_engine.getKey(GLFW_KEY_SPACE))
    {
        show_imgui_window = true;
    }

    auto tempDir = m_camera.getDirection();
    const float speed{ 1.f };
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

    if (show_imgui_window)
    {
        ImGui::Begin("Hello, world!", &show_imgui_window);// Create a window called "Hello, world!" and append into it.

        ImGui::Checkbox("draw square", &m_drawSquare);
        ImGui::Text("Background");
        ImGui::ColorEdit3("clear color", (float*)&m_clearColor); // Edit 3 floats representing a color
        ImGui::DragFloat("Rotation speed [°/s]",&m_rotationSpeed,10.f,0.f,720.f,"%.0f");

        ImGui::DragFloat3("Camera Position", &m_camera.position[0]);
        ImGui::End();
    }
}