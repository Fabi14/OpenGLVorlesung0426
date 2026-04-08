#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <print>

std::string getOpenGLInfo()
{
    std::stringstream info;
    info << "Version: " << glGetString(GL_VERSION);
    return info.str();
}


int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;


    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!pWindow)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowPos(pWindow, 4000, 1200);

    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);


    std::print("{}", getOpenGLInfo());

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}