#pragma once

#include "Copper/ImGuiHandler.h"
#include "Copper/Window.h"
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
