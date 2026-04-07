#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <print>

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
}

int main()
{
    /* Initialize the library */
    if (!glfwInit())
        return EXIT_FAILURE;

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Load all OpenGL functions using the glfw loader function
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowPos(window, 4000, 1200);

    // set clear color
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

    std::print("{}", getGlInfoString());

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}