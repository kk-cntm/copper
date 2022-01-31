#include "cprpch.h"
#include "Copper/Core/Application.h"
#include "MacOsInput.h"
#include "GLFW/glfw3.h"

namespace Copper
{

bool MacOsInput::IsKeyPressed(int key) const
{
    int result = glfwGetKey(m_Window, key);

    return result == GLFW_PRESS || result == GLFW_REPEAT;
}

bool MacOsInput::IsMouseButtonPressed(int button) const
{
    int result = glfwGetMouseButton(m_Window, button);

    return result == GLFW_PRESS || result == GLFW_REPEAT;
}

std::pair<float, float> MacOsInput::GetMousePos() const
{
    double x, y;
    glfwGetCursorPos(m_Window, &x, &y);

    return std::make_pair(x, y);
}

}
