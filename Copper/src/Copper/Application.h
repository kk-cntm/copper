#pragma once

#include "Window.h"

namespace Copper
{

class Application
{
public:
    Application();
    virtual ~Application() = default;
    
    virtual int Run();
private:
    std::unique_ptr<Window> m_Window;
    bool m_Running = true;
};

// to be implemented by client
Application* CreateApplication();

}
