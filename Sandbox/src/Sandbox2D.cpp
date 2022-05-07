#include "Sandbox2D.h"

#include <Copper/Core/Application.h>
#include <Copper/Core/Log.h>
#include <Copper/Renderer/Renderer2D.h>
#include <Copper/Renderer/RenderCommand.h>

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
    : Copper::Layer("Sandbox2D")
{
    m_CameraController = std::make_shared<Copper::OrthoCameraController>(1280.0f / 720.0f);
    m_Texture = Copper::Texture2D::Create("assets/rocks.jpg");
}

void Sandbox2D::OnUpdate(Copper::Timestep ts)
{
    Copper::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
    Copper::RenderCommand::Clear();

    m_CameraController->OnUpdate(ts);

    Copper::Renderer2D::BeginScene(m_CameraController->GetCamera());
    Copper::Renderer2D::DrawQuad({ 0.2f, -0.2f }, { 0.3f, 0.3f }, { 0.1f, 0.3f, 0.8f, 1.0f });
    Copper::Renderer2D::DrawQuad({ -0.5f, 0.5f }, { 1.0f, 1.0f }, m_Texture);
    Copper::Renderer2D::EndScene();
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
