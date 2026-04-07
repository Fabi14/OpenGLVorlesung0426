#include "Engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <print>
#include "DebugOutput.h"

namespace
{
    std::string getGlInfoString()
    {
        std::stringstream info;
        info << "VENDOR: " << glGetString(GL_VENDOR) << '\n';
        info << "VERSION: " << glGetString(GL_VERSION) << '\n';
        //info << "RENDERER: " << glGetString(GL_RENDERER) << '\n';
        info << "SHADING_LANGUAGE_VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';
        return info.str();
    }

    void glfwErrorCallback(int code, const char* description)
    {
        std::println("Error code: {} ({})", code, description);
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
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef _DEBUG
//  create OpenGL in debug mode (required for DebugOutput)
    glfwWindowHint(GLFW_CONTEXT_DEBUG, true);
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

    // Load all OpenGL functions using the glfw loader function
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return false;
    }

    glfwSetWindowPos(pWindow, 4000, 1200);

    // set clear color
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

    std::print("{}", getGlInfoString());

#ifdef _DEBUG
    DebugOutput::enable();
#endif
    return true;
}

void Engine::run()
{
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();

        if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
        }
    }
}
