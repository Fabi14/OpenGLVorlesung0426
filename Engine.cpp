#include "Engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <print>
#include "DebugOutput.h"


namespace
{
    std::string getOpenGLInfo()
    {
        std::stringstream info;
        info << "Version: " << glGetString(GL_VERSION);
        return info.str();
    }

    void glfwErrorCallback(int error_code, const char* description)
    {
        std::print("Error Code: {} ({})", error_code, description);
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

    glfwSetErrorCallback(glfwErrorCallback);

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifdef _DEBUG
    glfwWindowHint(GLFW_CONTEXT_DEBUG, GLFW_TRUE);
#endif 

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

#ifdef _DEBUG
    DebugOutput::enable();
#endif // _DEBUG

    return true;
}

void Engine::run(const std::function<void()>& draw)
{
    if (!pWindow)
    {
        return;
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        draw();

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