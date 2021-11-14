#include "MacOsWindow.h"
#include "Copper/Log.h"

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
    m_Data.callback = callback;
}

void MacOsWindow::Shutdown()
{
    glfwDestroyWindow(m_Window);
}

}
