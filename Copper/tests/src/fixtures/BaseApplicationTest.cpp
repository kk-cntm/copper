#include "BaseApplicationTest.h"
#include "Copper/Debug/DebugProfiler.h"

void BaseApplicationTest::SetUpTestCase()
{
    Copper::Log::Init();
    CPR_PROFILER_INIT();
    CPR_PROFILER_START_SESSION("Test");
}

void BaseApplicationTest::TearDownTestCase() { CPR_PROFILER_END_SESSION(); }
