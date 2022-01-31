#pragma once

#include "Application.h"
#include "Log.h"

int main()
{
    Copper::Log::Init();
    
    CPR_WARN("Initialized app");
    CPR_CORE_INFO("Var a = {0}", 5);
    
    auto app = Copper::CreateApplication();
    
    return app->Run();
}

