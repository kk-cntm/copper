#include "OpenGLContext.h"
#include "Copper/Core/Log.h"
#include "glad/glad.h"

namespace Copper
{

OpenGLContext::OpenGLContext(GLFWwindow* window)
    : m_Window(window)
{
    Init();
}

void OpenGLContext::Init()
{
    glfwMakeContextCurrent(m_Window);
    int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    CPR_CORE_ASSERT(gladStatus, "Failed to load glad");

    CPR_CORE_INFO("OpenGL info:");
    CPR_CORE_INFO("    Vendor: {0}", glGetString(GL_VENDOR));
    CPR_CORE_INFO("    Renderer: {0}", glGetString(GL_RENDERER));
    CPR_CORE_INFO("    Version: {0}", glGetString(GL_VERSION));
}

void OpenGLContext::SwapBuffer()
{
    glfwSwapBuffers(m_Window);
}

}
