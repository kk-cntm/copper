#include "cprpch.h"
#include "Application.h"
#include "Event/ApplicationEvent.h"
#include "Log.h"
#include "ImGuiHandler.h"
#include "glad/glad.h"

namespace Copper
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application* Application::s_Instance = nullptr;

Application::Application()
{
    CPR_ASSERT(!s_Instance, "Application is a singleton");

    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
    m_ImGuiHandler = std::unique_ptr<ImGuiHandler>(ImGuiHandler::Create(*m_Window));

    glGenVertexArrays(1, &m_VertexArray);
    glBindVertexArray(m_VertexArray);

    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

    float vertices[3 * 3] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

    glGenBuffers(1, &m_IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

    unsigned int indices[3] = { 0, 1, 2 };

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    const char* vertexShaderSrc = "#version 410 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main() {\n"
        "gl_Position = vec4(aPos, 1.0f);\n"
        "}";
    const char* fragmetShaderSrc = "#version 410 core\n"
        "out vec4 FragColor;\n"
        "void main() { FragColor = vec4(1.0f, 0.2f, 0.6f, 1.0f); }";

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmetShaderSrc, nullptr);
    glCompileShader(fragmentShader);

    m_Shader = glCreateProgram();
    glAttachShader(m_Shader, vertexShader);
    glAttachShader(m_Shader, fragmentShader);
    glLinkProgram(m_Shader);

    s_Instance = this;
}

int Application::Run()
{
    while (m_Running)
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(m_Shader);
        glBindVertexArray(m_VertexArray);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        for (Layer* layer : m_LayerStack)
            layer->OnUpdate();

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
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

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
