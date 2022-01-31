#pragma once

#include "Copper/Core/ImGuiHandler.h"
#include "Copper/Core/Window.h"
#include "MacOsWindow.h"

namespace Copper
{

class MacOsImGuiHandler : public ImGuiHandler
{
public:
    MacOsImGuiHandler(MacOsWindow& window);
    virtual ~MacOsImGuiHandler();

    virtual void Begin() override;
    virtual void End() override;
};

}
