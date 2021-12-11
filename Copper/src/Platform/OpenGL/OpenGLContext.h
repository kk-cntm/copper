#pragma once

#include "Copper/Renderer/GraphicContext.h"
#include "GLFW/glfw3.h"

namespace Copper
{

class OpenGLContext : public GraphicContext
{
public:
    OpenGLContext(GLFWwindow* window);

    virtual void SwapBuffer() override;

private:
    void Init();

    GLFWwindow* m_Window;
};

}
