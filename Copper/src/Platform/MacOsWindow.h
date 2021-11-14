#pragma once

#include "Copper/Window.h"
#include "GLFW/glfw3.h"

namespace Copper
{

class MacOsWindow : public Window
{
public:
    MacOsWindow(const WindowProps& props);
    virtual ~MacOsWindow();
    
    virtual void OnUpdate() override;

    inline virtual unsigned int GetWidth() const override { return m_Data.Width; };
    inline virtual unsigned int GetHeight() const override { return m_Data.Height; };

    virtual void SetEventCallback(const Window::EventCallbackFn& callback) override;
    virtual void SetVSync(bool enabled) override;
    virtual bool IsVSync() const override;
private:
    virtual void Init(const WindowProps& props);
    virtual void Shutdown();
    
    GLFWwindow* m_Window;
    
    struct WindowData
    {
        unsigned int Width;
        unsigned int Height;
        std::string Title;
        bool VSync;
        EventCallbackFn callback;
    };
    
    WindowData m_Data;
};

}
