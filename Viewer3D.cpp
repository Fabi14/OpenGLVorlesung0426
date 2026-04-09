#include "Viewer3D.h"
#include <glad/glad.h>
#include <array>
#include <glm/glm.hpp>
#include <span>
#include "Shader.h"


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
    Shader vertexShader("VertexShader.glsl", GL_VERTEX_SHADER);
    // FragmentShader
    Shader fragmentShader("FragmentShader.glsl", GL_FRAGMENT_SHADER);
    // -> ShaderProgram
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader.get());
    glAttachShader(shaderProgram, fragmentShader.get());

    glLinkProgram(shaderProgram);

    glDetachShader(shaderProgram, vertexShader.get());
    glDetachShader(shaderProgram, fragmentShader.get());

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
    glUseProgram(shaderProgram);
    //draw 
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
