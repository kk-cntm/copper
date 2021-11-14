#include "cprpch.h"
#include "Application.h"
#include "Event/ApplicationEvent.h"
#include "Log.h"

namespace Copper
{

Application::Application()
{
    m_Window = std::unique_ptr<Window>(Window::Create());
}

int Application::Run()
{
    while (m_Running)
    {
        m_Window->OnUpdate();
    }

    return 0;
}

}
