#include "cprpch.h"
#include "MacOsWindow.h"
#include "Copper/Log.h"
#include "Copper/Event/MouseEvent.h"
#include "Copper/Event/ApplicationEvent.h"
#include "Copper/Event/KeyEvent.h"

namespace Copper
{

static bool s_GLFWInitialized = false;

Window* Window::Create(const WindowProps& props)
{
    return new MacOsWindow(props);
}

MacOsWindow::MacOsWindow(const WindowProps& props)
{
    Init(props);
}

MacOsWindow::~MacOsWindow()
{
    Shutdown();
}

void MacOsWindow::Init(const WindowProps& props)
{
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;

    CPR_CORE_INFO("Creating mainwindow {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);
    
    if (!s_GLFWInitialized)
    {
        int success = glfwInit();
        
        CPR_CORE_ASSERT(success, "Could not initialize GLFW");
        
        s_GLFWInitialized = true;
    }
    
    m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), NULL, nullptr);
    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, &m_Data);

    glfwSetErrorCallback(&MacOsWindow::OnGLFWError);
    glfwSetMouseButtonCallback(m_Window, &MacOsWindow::OnGLFWMouseButton);
    glfwSetKeyCallback(m_Window, &MacOsWindow::OnGLFWKey);
    glfwSetWindowCloseCallback(m_Window, &MacOsWindow::OnGLFWWindowClose);
    glfwSetWindowSizeCallback(m_Window, &MacOsWindow::OnGLFWWindowResize);
    glfwSetCursorPosCallback(m_Window, &MacOsWindow::OnGLFWMouseMove);

    SetVSync(true);
}

void MacOsWindow::OnUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

void MacOsWindow::SetVSync(bool enabled)
{
    glfwSwapInterval(enabled ? 1 : 0);
    m_Data.VSync = enabled;
}

bool MacOsWindow::IsVSync() const
{
    return m_Data.VSync;
}

void MacOsWindow::SetEventCallback(const Window::EventCallbackFn& callback)
{
    m_Data.EventCallback = callback;
}

void MacOsWindow::OnGLFWMouseButton(GLFWwindow* window, int button, int action, int /*mode*/)
{
    WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

    switch (action) {
    case GLFW_PRESS:
    {
        MouseButtonPressedEvent event(button);
        data.EventCallback(event);
        break;
    }

    case GLFW_RELEASE:
    {
        MouseButtonReleasedEvent event(button);
        data.EventCallback(event);
        break;
    }

    default:
        CPR_CORE_WARN("MacOsWindow::OnGLFWMouseButton unhandled event: {0} {1} {2}", button, action);
    }
}

void MacOsWindow::OnGLFWMouseMove(GLFWwindow* window, double x, double y)
{
    WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

    MouseMovedEvent event(x, y);
    data.EventCallback(event);
}

void MacOsWindow::OnGLFWWindowClose(GLFWwindow* window)
{
    WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

    WindowCloseEvent event;
    data.EventCallback(event);
}

void MacOsWindow::OnGLFWWindowResize(GLFWwindow* window, int width, int height)
{
    WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

    WindowResizeEvent event(width, height);
    data.EventCallback(event);
}

void MacOsWindow::OnGLFWKey(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
{
    WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

    switch (action) {
    case GLFW_PRESS:
    {
        KeyPressedEvent event(key, 0);
        data.EventCallback(event);
        break;
    }

    case GLFW_RELEASE:
    {
        KeyReleasedEvent event(key);
        data.EventCallback(event);
        break;
    }

    case GLFW_REPEAT:
    {
        KeyPressedEvent event(key, 1);
        data.EventCallback(event);
        break;
    }

    default:
        CPR_CORE_WARN("MacOsWindow::OnGLFWKey unhandled event: {0} {1}", key, action);
    }
}

void MacOsWindow::OnGLFWError(int error, const char* description)
{
    CPR_CORE_ERROR("MacOsWindow::OnGLFWError: {0}, {1}", error, description);
}

void MacOsWindow::Shutdown()
{
    glfwDestroyWindow(m_Window);
}

}
