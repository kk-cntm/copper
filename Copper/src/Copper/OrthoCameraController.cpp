#include "OrthoCameraController.h"
#include "Copper/Application.h"
#include "Copper/KeyCodes.h"

namespace Copper
{

OrthoCameraController::OrthoCameraController(float aspectRatio)
    : m_ZoomLevel(1.0f),
      m_AspectRatio(aspectRatio),
      m_CameraRotateSpeed(30.0f),
      m_CameraTranslateSpeed(0.5f),
      m_Camera(std::make_shared<OrthoCamera>(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)) {}

void OrthoCameraController::OnUpdate(Timestep ts)
{
    const auto& input = Copper::Application::Get().GetWindow().GetInput();
    glm::vec3 position = m_Camera->GetPosition();
    float rotation = m_Camera->GetRotation();

    if (input.IsKeyPressed(CPR_KEY_W))
        position.y += m_CameraTranslateSpeed * ts;
    else if (input.IsKeyPressed(CPR_KEY_S))
        position.y -= m_CameraTranslateSpeed * ts;

    if (input.IsKeyPressed(CPR_KEY_A))
        position.x -= m_CameraTranslateSpeed * ts;
    else if (input.IsKeyPressed(CPR_KEY_D))
        position.x += m_CameraTranslateSpeed * ts;

    if (input.IsKeyPressed(CPR_KEY_Q))
        rotation -= m_CameraRotateSpeed * ts;
    else if (input.IsKeyPressed(CPR_KEY_E))
        rotation += m_CameraRotateSpeed * ts;

    m_Camera->SetPosition(position);
    m_Camera->SetRotation(rotation);
}

void OrthoCameraController::OnEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    
    dispatcher.Dispatch<WindowFBResizeEvent>(CPR_EVENT_FN(OrthoCameraController::OnWindowResized));
    dispatcher.Dispatch<MouseScrollEvent>(CPR_EVENT_FN(OrthoCameraController::OnMouseScrolled));
}

bool OrthoCameraController::OnWindowResized(WindowFBResizeEvent& e)
{
    m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();

    m_Camera->SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

    return false;
}

bool OrthoCameraController::OnMouseScrolled(MouseScrollEvent& e)
{
    m_ZoomLevel -= e.GetOffsetY();

    if (m_ZoomLevel < 0.25f)
        m_ZoomLevel = 0.25f;

    m_Camera->SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    
    return false;
}

}
