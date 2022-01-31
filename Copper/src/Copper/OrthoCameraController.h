#pragma once

#include "Copper/Core/Core.h"
#include "Copper/Core/Timestep.h"
#include "Copper/Renderer/OrthoCamera.h"
#include "Copper/Event/Event.h"
#include "Copper/Event/ApplicationEvent.h"
#include "Copper/Event/MouseEvent.h"

namespace Copper
{

class COPPER_API OrthoCameraController
{
public:
    OrthoCameraController(float aspectRation);
    
    void OnEvent(Event& e);
    void OnUpdate(Timestep ts);

    inline const Ref<OrthoCamera>& GetCamera() { return m_Camera; }

private:
    bool OnWindowResized(WindowFBResizeEvent& e);
    bool OnMouseScrolled(MouseScrollEvent& e);
    
    float m_CameraTranslateSpeed;
    float m_CameraRotateSpeed;
    float m_ZoomLevel;
    float m_AspectRatio;
    Ref<OrthoCamera> m_Camera;
};

}
