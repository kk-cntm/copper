#pragma once

#include "Event.h"

namespace Copper
{

class MouseMovedEvent : public Event
{
public:
    MouseMovedEvent(float x, float y)
       : m_X(x),
         m_Y(y) {}
    
    inline float GetX() { return m_X; }
    inline float GetY() { return m_Y; }
    
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseModedEvent: (" << m_X, ", " << m_Y << ")";
        return ss.str();
    }
    
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    EVENT_CLASS_TYPE(MouseMoved)
private:
    float m_X, m_Y;
};

class MouseScrollEvent : public Event
{
public:
    MouseScrollEvent(float xOffset, float yOffset)
       : m_XOffset(x),
         m_YOffset(y) {}

    inline float GetOffsetX() { return m_XOffset; }
    inline float GetOffsetY() { return m_YOffset; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseScrollEvent: " << m_XOffset, ", " << m_Y;
        return ss.str();
    }

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    EVENT_CLASS_TYPE(MouseScroll)
private:
    float m_XOffset, m_YOffset;
};

class MouseButtonEvent : public Event
{
public:
    inline int GetMouseButton() { return m_Button; }

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
protected:
    MouseButtonEvent(int button)
       : m_Button(button)
    {
    }

    int m_Button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
    MouseButtonReleasedEvent(int button)
       : MouseButtonEvent(button) {}
    
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << m_Button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
    MouseButtonReleasedEvent(int button)
       : MouseButtonEvent(button) {}
    
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << m_Button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)
};

}
