#pragma once

#include "Event.h"

namespace Copper
{

class ResizeEvent : public Event
{
public:
    inline unsigned int GetWidth() { return m_Width; }
    inline unsigned int GetHeight() { return m_Height; }

protected:
    ResizeEvent(unsigned int width, unsigned int height)
        : m_Width(width),
          m_Height(height) {}

    unsigned int m_Width;
    unsigned int m_Height;
};

class WindowResizeEvent : public ResizeEvent
{
public:
    WindowResizeEvent(unsigned int width, unsigned int height)
        : ResizeEvent(width, height) {}

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
        return ss.str();
    }
    
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
    EVENT_CLASS_TYPE(WindowResize)
};

class WindowFBResizeEvent : public ResizeEvent
{
public:
    WindowFBResizeEvent(unsigned int width, unsigned int height)
        : ResizeEvent(width, height) {}

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "WindowFBResizeEvent: " << m_Width << ", " << m_Height;
        return ss.str();
    }

    EVENT_CLASS_CATEGORY(EventCategoryApplication)
    EVENT_CLASS_TYPE(WindowFbResize)
};

class WindowCloseEvent : public Event
{
public:
    WindowCloseEvent() {}
    
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
    EVENT_CLASS_TYPE(WindowClose)
};

class AppTickEvent : public Event
{
public:
    AppTickEvent() {}
    
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
    EVENT_CLASS_TYPE(AppTick)
};

class AppUpdateEvent : public Event
{
public:
    AppUpdateEvent() {}
    
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
    EVENT_CLASS_TYPE(AppUpdate)
};

class AppRenderEvent : public Event
{
public:
    AppRenderEvent() {}
    
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
    EVENT_CLASS_TYPE(AppRender)
};

}
