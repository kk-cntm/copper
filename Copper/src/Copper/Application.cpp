#include "cprpch.h"
#include "Copper/Core.h"
#include "Application.h"
#include "Event/ApplicationEvent.h"
#include "Log.h"
#include "ImGuiHandler.h"
#include "Renderer/Renderer.h"
#include "Platform.h"
#include "Timestep.h"

namespace Copper
{

Application* Application::s_Instance = nullptr;

Application::Application()
{
    CPR_ASSERT(!s_Instance, "Application is a singleton");

    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(CPR_EVENT_FN(Application::OnEvent));
    m_ImGuiHandler = std::unique_ptr<ImGuiHandler>(ImGuiHandler::Create(*m_Window));

    Renderer::Init();

    s_Instance = this;
}

int Application::Run()
{
    float time = Platform::GetTime();
    Timestep ts = time - m_LastFrameTime;
    m_LastFrameTime = time;

    while (m_Running)
    {
        for (Layer* layer : m_LayerStack)
            layer->OnUpdate(ts);

        m_ImGuiHandler->Begin();
        for (Layer* layer : m_LayerStack)
            layer->OnImGuiUpdate();
        m_ImGuiHandler->End();

        m_Window->OnUpdate();
    }

    return 0;
}

void Application::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);

    dispatcher.Dispatch<WindowCloseEvent>(CPR_EVENT_FN(Application::OnWindowClose));
    dispatcher.Dispatch<WindowFBResizeEvent>(Renderer::OnWindowFbResize);

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
    {
        (*--it)->OnEvent(event);
        if (event.IsHandled())
            break;
    }
}

bool Application::OnWindowClose(WindowCloseEvent& event)
{
    m_Running = false;

    return true;
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
