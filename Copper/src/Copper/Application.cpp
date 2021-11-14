#include "cprpch.h"
#include "Application.h"
#include "Event/ApplicationEvent.h"
#include "Log.h"

namespace Copper
{

Application::Application()
{
    m_Window = std::unique_ptr<Window>(Window::Create());
}

int Application::Run()
{
    while (m_Running)
    {
        for (Layer* layer : m_LayerStack)
            layer->OnUpdate();

        m_Window->OnUpdate();
    }

    return 0;
}

void Application::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);

    CPR_CORE_TRACE("{0}", event);

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
    {
        (*--it)->OnEvent(event);
        if (event.IsHandled())
            break;
    }
}

void Application::PushLayer(Layer* layer)
{
    m_LayerStack.PushLayer(layer);
}

void Application::PushOverlaye(Layer* overlay)
{
    m_LayerStack.PushOverlay(overlay);
}

}
