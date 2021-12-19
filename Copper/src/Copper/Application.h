#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Event/ApplicationEvent.h"
#include "ImGuiHandler.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Copper/Renderer/Buffer.h"

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

    unsigned int m_VertexArray;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<OpenGLShader> m_Shader;

    static Application* s_Instance;
};

// to be implemented by client
Application* CreateApplication();

}
