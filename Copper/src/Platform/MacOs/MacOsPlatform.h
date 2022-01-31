#pragma once

#include "Copper/Core/Platform.h"
#include "GLFW/glfw3.h"

namespace Copper
{

class MacOsPlatform : public Platform
{
private:
    inline virtual float GetTimeImpl() const override { return glfwGetTime(); }
};

}
