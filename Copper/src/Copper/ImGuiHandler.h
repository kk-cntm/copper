#pragma once

#include "Event/Event.h"
#include "Window.h"

namespace Copper
{

class ImGuiHandler
{
public:
    virtual ~ImGuiHandler() {}

    virtual void Begin() = 0;
    virtual void End() = 0;

    static ImGuiHandler* Create(Window& window);
};

}
