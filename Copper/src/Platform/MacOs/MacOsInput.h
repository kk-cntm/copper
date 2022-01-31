#pragma once

#include "Copper/Core/Input.h"
#include "GLFW/glfw3.h"

namespace Copper
{

class MacOsInput : public Input
{
public:
    MacOsInput(GLFWwindow* window)
        : m_Window(window) {}

    virtual bool IsKeyPressed(int key) const override;
    virtual bool IsMouseButtonPressed(int button) const override;
    virtual std::pair<float, float> GetMousePos() const override;
private:
    GLFWwindow* m_Window;
};

}
