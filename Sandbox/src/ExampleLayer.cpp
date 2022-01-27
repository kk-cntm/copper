#include "ExampleLayer.h"
#include "Copper/Log.h"
#include "Copper/Application.h"
#include "Copper/Renderer/Renderer.h"
#include "Copper/Renderer/Texture.h"
#include "Copper/KeyCodes.h"
#include "Copper/Application.h"

#include "imgui/imgui.h"
#include "glm/glm.hpp"

ExampleLayer::ExampleLayer()
    : Copper::Layer("ExampleLayer")
{
    m_Camera = std::make_shared<Copper::OrthoCamera>(-1.0f, 1.0f, -1.0f, 1.0f);
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

    const auto& input = Copper::Application::Get().GetWindow().GetInput();

    if (input.IsKeyPressed(CPR_KEY_UP))
        m_CameraPosition.y += m_CameraMoveSpeed * ts;
    else if (input.IsKeyPressed(CPR_KEY_DOWN))
        m_CameraPosition.y -= m_CameraMoveSpeed * ts;

    if (input.IsKeyPressed(CPR_KEY_LEFT))
        m_CameraPosition.x -= m_CameraMoveSpeed * ts;
    else if (input.IsKeyPressed(CPR_KEY_RIGHT))
        m_CameraPosition.x += m_CameraMoveSpeed * ts;

    if (input.IsKeyPressed(CPR_KEY_A))
        m_CameraRotation -= m_CameraRotationSpeed * ts;
    else if (input.IsKeyPressed(CPR_KEY_D))
        m_CameraRotation += m_CameraRotationSpeed * ts;

    m_Camera->SetPosition(m_CameraPosition);
    m_Camera->SetRotation(m_CameraRotation);

    Copper::Renderer::BeginScene(m_Camera);

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
}
