#include "OpenGLContext.h"
#include "Copper/Log.h"
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
}

void OpenGLContext::SwapBuffer()
{
    glfwSwapBuffers(m_Window);
}

}
