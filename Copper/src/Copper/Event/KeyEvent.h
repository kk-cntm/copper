#pragma once

#include "Event.h"

namespace Copper
{

class KeyEvent : public Event
{
public:
    inline GetKeyCode() const { return m_KeyCode; }
    
    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
protected:
    KeyEvent(int keyCode)
        : m_KeyCode(keyCode) {}
    
    int m_KeyCode;
};

class KeyPressedEvent : public KeyEvent
{
public:
    KeyPressedEvent(int keyCode, int repeatCount)
        : KeyEvent(keyCode),
          m_RepeatCount(repeatCount) {}
    
    inline GetRepeatCount() const { return m_RepeatCount; }
    
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
        return ss.str();
    }
    
    EVENT_CLASS_TYPE(KeyPressed)
protected:
    int m_RepeatCount;
};

class KeyReleasedEvent : public KeyEvent
{
public:
    KeyReleasedEvent(int keyCode)
        : KeyEvent(keyCode) {}
    
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << m_KeyCode;
        return ss.str();
    }
    
    EVENT_CLASS_TYPE(KeyReleased)
};

}