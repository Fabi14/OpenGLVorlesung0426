#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


int main()
{
    /* Initialize the library */
    if (!glfwInit())
        return EXIT_FAILURE;

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

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}