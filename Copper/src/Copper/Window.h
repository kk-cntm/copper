#pragma once

#include "cprpch.h"
#include "Event/Event.h"
#include "Input.h"

namespace Copper
{

struct WindowProps
{
    std::string Title;
    unsigned int Width;
    unsigned int Height;
    
    WindowProps(const std::string& title = "Copper engine",
                unsigned int width = 1280,
                unsigned int height = 720)
        : Title(title),
          Width(width),
          Height(height) {}
};

class Window
{
public:
    using EventCallbackFn = std::function<void(Event&)>;

    virtual ~Window() {}
    
    virtual void OnUpdate() = 0;

    virtual unsigned int GetWidth() const = 0;
    virtual unsigned int GetHeight() const = 0;

    virtual std::pair<float, float> GetDPI() const = 0;

    virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
    virtual void SetVSync(bool enabled) = 0;
    virtual bool IsVSync() const = 0;

    virtual const Input& GetInput() const = 0;

    static Window* Create(const WindowProps& props = WindowProps());
};

}
