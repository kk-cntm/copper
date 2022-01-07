#include "ExampleLayer.h"
#include "Copper/Log.h"
#include "Copper/Application.h"
#include "Copper/Renderer/Renderer.h"
#include "imgui/imgui.h"

ExampleLayer::ExampleLayer()
    : Copper::Layer("ExampleLayer")
{
    m_Camera = std::make_shared<Copper::OrthoCamera>(-1.0f, 1.0f, -1.0f, 1.0f);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.2f, 0.1f, 0.8f, 1.0f,
         0.5f, -0.5f, 0.0f, 0.7f, 0.4f, 0.3f, 1.0f,
         0.0f,  0.5f, 0.0f, 0.4f, 0.9f, 0.5f, 1.0f
    };

    std::shared_ptr<Copper::VertexBuffer> vertexBuffer(Copper::VertexBuffer::Create(vertices, 21));

    Copper::BufferLayout layout = {
        { Copper::ShaderData::Type::Float3, "a_Position" },
        { Copper::ShaderData::Type::Float4, "a_Color" }
    };

    vertexBuffer->SetLayout(layout);

    uint32_t indices[] = { 0, 1, 2 };
    std::shared_ptr<Copper::IndexBuffer> indexBuffer(Copper::IndexBuffer::Create(indices, 3));

    m_VertexArray = std::shared_ptr<Copper::VertexArray>(Copper::VertexArray::Create());

    m_VertexArray->AddVertexBuffer(vertexBuffer);
    m_VertexArray->SetIndexBuffer(indexBuffer);

    std::string vertexShaderSrc = "#version 410 core\n"
        "layout (location = 0) in vec3 a_Position;\n"
        "layout (location = 1) in vec4 a_Color;\n"
        "out vec4 v_Color;\n"
        "uniform mat4 u_ViewProjectionMatrix;\n"
        "void main() {\n"
        "gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0f);\n"
        "v_Color = a_Color;\n"
        "}";
    std::string fragmetShaderSrc = "#version 410 core\n"
        "out vec4 FragColor;\n"
        "in vec4 v_Color;\n"
        "void main() { FragColor = v_Color; }";

    m_Shader = std::shared_ptr<Copper::Shader>(
        Copper::Shader::Create(vertexShaderSrc, fragmetShaderSrc));
}

void ExampleLayer::OnEvent(Copper::Event& event)
{
}

void ExampleLayer::OnUpdate()
{
    Copper::Renderer::BeginScene(m_Camera);

    Copper::Renderer::Submit({ m_VertexArray, m_Shader });

    Copper::Renderer::EndScene();
}

void ExampleLayer::OnImGuiUpdate()
{
    static bool show = true;
    if (show)
        ImGui::ShowDemoWindow(&show);
}
