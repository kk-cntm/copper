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

    virtual std::pair<float, float> GetDPI() const override;

    virtual void SetEventCallback(const Window::EventCallbackFn& callback) override;
    virtual void SetVSync(bool enabled) override;
    virtual bool IsVSync() const override;
private:
    static void OnGLFWMouseButton(GLFWwindow* window, int button, int actions, int mode);
    static void OnGLFWMouseMove(GLFWwindow* window, double x, double y);
    static void OnGLFWWindowClose(GLFWwindow* window);
    static void OnGLFWWindowResize(GLFWwindow* window, int width, int height);
    static void OnGLFWWindowFbResize(GLFWwindow* window, int width, int height);
    static void OnGLFWKey(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void OnGLFWError(int error, const char* description);

    virtual void Init(const WindowProps& props);
    virtual void Shutdown();

    GLFWmonitor* GetCurrentMonitor() const;

    GLFWwindow* m_Window;
    
    struct WindowData
    {
        unsigned int Width = 0;
        unsigned int Height = 0;
        unsigned int FbWidth = 0;
        unsigned int FbHeight = 0;
        std::string Title;
        bool VSync = false;
        EventCallbackFn EventCallback;
    };

    WindowData m_Data;
};

}
