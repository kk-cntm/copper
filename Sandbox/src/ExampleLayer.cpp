#include "ExampleLayer.h"
#include "Copper/Core/Log.h"
#include "Copper/Core/Application.h"
#include "Copper/Renderer/Renderer.h"
#include "Copper/Renderer/Texture.h"
#include "Copper/Core/KeyCodes.h"

#include "imgui/imgui.h"
#include "glm/glm.hpp"

ExampleLayer::ExampleLayer()
    : Copper::Layer("ExampleLayer")
{
    m_CameraController = std::make_shared<Copper::OrthoCameraController>(1280.0f / 720.0f);
    m_Texture = Copper::Texture2D::Create("assets/rocks.jpg");
    m_HologramWaterTexture = Copper::Texture2D::Create("assets/magnify.png");
    m_Shader = m_ShaderLibrary.Load("assets/texture.glsl");

    float vertices[] = {
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f
    };

    auto vertexBuffer = Copper::VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float));

    Copper::BufferLayout layout = {
        { Copper::ShaderData::Type::Float3, "a_Position" },
        { Copper::ShaderData::Type::Float2, "a_TexPos" }
    };

    vertexBuffer->SetLayout(layout);

    uint32_t indices[] = { 0, 1, 2, 0, 2, 3 };
    auto indexBuffer = Copper::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

    m_VertexArray = Copper::Ref<Copper::VertexArray>(Copper::VertexArray::Create());

    m_VertexArray->AddVertexBuffer(vertexBuffer);
    m_VertexArray->SetIndexBuffer(indexBuffer);
}

void ExampleLayer::OnUpdate(Copper::Timestep ts)
{
    Copper::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
    Copper::RenderCommand::Clear();

    m_CameraController->OnUpdate(ts);

    Copper::Renderer::BeginScene(m_CameraController->GetCamera());

    glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
    Copper::Renderer::Submit({ m_VertexArray, m_Shader, m_Texture, transform });
    Copper::Renderer::Submit({ m_VertexArray, m_Shader, m_HologramWaterTexture, transform });

    Copper::Renderer::EndScene();
}

void ExampleLayer::OnImGuiUpdate()
{
    static bool show = true;
    if (show)
        ImGui::ShowDemoWindow(&show);
}

void ExampleLayer::OnEvent(Copper::Event& event)
{
    m_CameraController->OnEvent(event);
}
