#include "DebugOutput.h"
#include <print>
#include <glad/glad.h>
#include "Shader.h"

namespace
{
    void MessageCallback(GLenum /*source*/,
        GLenum type,
        GLuint /*id*/,
        GLenum severity,
        GLsizei /*length*/,
        const GLchar* message,
        const void* /*userParam*/)
    {
        std::println("GL CALLBACK : {} type = 0x{:x}, severity = 0x{:x}, message = {}", (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            type, severity, message);
    }
}

void DebugOutput::enable()
{
    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(MessageCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
    else
    {
        std::println("No GLFW_OPENGL_DEBUG_CONTEXT");
    }
}

void DebugOutput::checkShaderCompilation(const Shader& shader)
{
    GLint success = 0;
    glGetShaderiv(shader.get(), GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        int len;
        glGetShaderiv(shader.get(), GL_INFO_LOG_LENGTH, &len);
        std::string errorString;
        errorString.resize(len);
        glGetShaderInfoLog(shader.get(), len, nullptr, errorString.data());
        std::println("Error in Shader: {}", errorString);
    }
}