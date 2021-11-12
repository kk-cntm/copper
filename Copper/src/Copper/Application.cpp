#include "Application.h"
#include "Event/ApplicationEvent.h"
#include "Log.h"
#include <stdio.h>

namespace Copper
{

int Application::Run()
{
    WindowResizeEvent event(1200, 1000);
    CPR_INFO(event);
    
    return 0;
}

}
