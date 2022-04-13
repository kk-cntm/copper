#include "Sandbox2D.h"

#include <Copper/Core/Application.h>
#include <Copper/Core/Log.h>
#include <Copper/Renderer/Renderer.h>

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
    : Copper::Layer("Sandbox2D")
{
    m_CameraController = std::make_shared<Copper::OrthoCameraController>(1280.0f / 720.0f);
    m_FlatColorShader = m_ShaderLibrary.Load("assets/FlatColor.glsl");

    float vertices[] = { -0.5f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f };

    auto vertexBuffer = Copper::VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float));

    Copper::BufferLayout layout = { { Copper::ShaderData::Type::Float3, "a_Position" } };

    vertexBuffer->SetLayout(layout);

    uint32_t indices[] = { 0, 1, 2, 0, 2, 3 };
    auto indexBuffer = Copper::IndexBuffer::Create(indices,sizeof(indices) / sizeof(uint32_t));

    m_VertexArray = Copper::VertexArray::Create();

    m_VertexArray->AddVertexBuffer(vertexBuffer);
    m_VertexArray->SetIndexBuffer(indexBuffer);
}

void Sandbox2D::OnUpdate(Copper::Timestep ts)
{
    Copper::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
    Copper::RenderCommand::Clear();

    m_CameraController->OnUpdate(ts);

    Copper::Renderer::BeginScene(m_CameraController->GetCamera());

    m_FlatColorShader->SetUniform("u_Color", m_Color);

    glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
    Copper::Renderer::Submit({ m_VertexArray, m_FlatColorShader, nullptr, transform });

    Copper::Renderer::EndScene();
}

void Sandbox2D::OnImGuiUpdate()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Edit color", glm::value_ptr(m_Color));
    ImGui::End();
}

void Sandbox2D::OnEvent(Copper::Event& event)
{
    m_CameraController->OnEvent(event);
}
