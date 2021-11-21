#pragma once

#include "Copper/Layer.h"
#include "Copper/Event/Event.h"
#include "Copper/Event/MouseEvent.h"
#include "Copper/Event/KeyEvent.h"
#include "Copper/Event/ApplicationEvent.h"

namespace Copper
{

class DebugLayer : public Layer
{
public:
    DebugLayer();
    ~DebugLayer();
    
    void OnAttach() override;
    void OnDetach() override;
    void OnEvent(Event& event) override;
    void OnUpdate() override;
private:
    bool OnMouseMoveEvent(MouseMovedEvent& event);
    bool OnMouseButtonPressEvent(MouseButtonPressedEvent& event);
    bool OnMouseButtonReleaseEvent(MouseButtonReleasedEvent& event);
    bool OnMouseScrollEvent(MouseScrollEvent& event);
    bool OnKeyPressEvent(KeyPressedEvent& event);
    bool OnKeyReleaseEvent(KeyReleasedEvent& event);
    bool OnWindowResizeEvent(WindowResizeEvent& event);

    float m_Time = 0;
};

}
