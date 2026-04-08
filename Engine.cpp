#include "Engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <print>

namespace
{
    std::string getOpenGLInfo()
    {
        std::stringstream info;
        info << "Version: " << glGetString(GL_VERSION);
        return info.str();
    }
}

Engine::~Engine()
{
    glfwTerminate();
}

bool Engine::init()
{
    /* Initialize the library */
    if (!glfwInit())
        return false;

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    /* Create a windowed mode window and its OpenGL context */
    pWindow = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!pWindow)
    {
        glfwTerminate();
        return false;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return false;
    }

    glfwSetWindowPos(pWindow, 4000, 1200);
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    std::print("{}", getOpenGLInfo());
    return true;
}

void Engine::run()
{
    if (!pWindow)
    {
        return;
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();

        if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
        }
    }
}
