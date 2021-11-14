#pragma once

#include "Window.h"
#include "LayerStack.h"
#include "Event/ApplicationEvent.h"

namespace Copper
{

class Application
{
public:
    Application();
    virtual ~Application() = default;
    
    virtual int Run();

    void OnEvent(Event& event);
    bool OnWindowClose(WindowCloseEvent& event);

    void PushLayer(Layer* layer);
    void PushOverlaye(Layer* overlay);
private:
    std::unique_ptr<Window> m_Window;
    bool m_Running = true;
    LayerStack m_LayerStack;
};

// to be implemented by client
Application* CreateApplication();

}
