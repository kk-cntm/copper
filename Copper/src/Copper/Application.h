#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Event/ApplicationEvent.h"
#include "ImGuiHandler.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/OrthoCamera.h"

namespace Copper
{

class COPPER_API Application
{
public:
    Application();
    virtual ~Application() = default;
    
    virtual int Run();

    void OnEvent(Event& event);
    bool OnWindowClose(WindowCloseEvent& event);

    void PushLayer(Layer* layer);
    void PushOverlaye(Layer* overlay);

    inline const Window& GetWindow() const { return *m_Window; }
    
    inline static const Application& Get() { return *s_Instance; }
private:
    std::unique_ptr<Window> m_Window;
    std::unique_ptr<ImGuiHandler> m_ImGuiHandler;
    bool m_Running = true;
    LayerStack m_LayerStack;

    static Application* s_Instance;
};

// to be implemented by client
Application* CreateApplication();

}
