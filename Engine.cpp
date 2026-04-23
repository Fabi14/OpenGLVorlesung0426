#include "Engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <print>
#include "DebugOutput.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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

    void onSize(GLFWwindow*, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
}

Engine::~Engine()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
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
    m_pWindow = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!m_pWindow)
    {
        glfwTerminate();
        return false;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_pWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return false;
    }

    glfwSetWindowPos(m_pWindow, 4000, 1200);
    glfwSetWindowSizeCallback(m_pWindow, onSize);

    std::print("{}", getOpenGLInfo());

#ifdef _DEBUG
    DebugOutput::enable();
#endif // _DEBUG

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_pWindow, true);
    ImGui_ImplOpenGL3_Init("#version 460");


    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    glEnable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

void Engine::run(const std::function<void(double)>& update)
{
    if (!m_pWindow)
    {
        return;
    }
    //bool show_demo_window = false;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(m_pWindow))
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        //ImGui::ShowDemoWindow(&show_demo_window);

        /* Render here */
        auto now = glfwGetTime();
        auto deltaTime = now - m_time;
        m_time = now;
        update(deltaTime);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(m_pWindow);

        /* Poll for and process events */
        glfwPollEvents();

        if (glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(m_pWindow, GLFW_TRUE);
        }
    }
}

bool Engine::getKey(int glfw_Key) const
{
    return glfwGetKey(m_pWindow, glfw_Key);
}

glm::vec2 Engine::getMousePos() const
{
    double x{};
    double y{};
    glfwGetCursorPos(m_pWindow, &x, &y);

    return { x,y };
}

bool Engine::getMouseButton(int button) const
{
    return glfwGetMouseButton(m_pWindow, button) == GLFW_PRESS;
}

float Engine::getWindowAspectRatio() const
{
    auto size = getWindowSize();
    return size.x/size.y;
}

glm::vec2 Engine::getWindowSize() const
{
    int w{};
    int h{};
    glfwGetWindowSize(m_pWindow, &w, &h);
    return { static_cast<float>(w),  static_cast<float>(h) };
}
