#pragma once

#include "Copper/Debug/DebugProfiler.h"
#include "Application.h"
#include "Log.h"

int main()
{
    Copper::Log::Init();
    CPR_PROFILER_INIT();

    CPR_PROFILER_START_SESSION("Start");
    auto app = Copper::CreateApplication();
    CPR_PROFILER_END_SESSION();

    CPR_PROFILER_START_SESSION("Run");
    const int code = app->Run();
    CPR_PROFILER_END_SESSION();

    return code;
}

