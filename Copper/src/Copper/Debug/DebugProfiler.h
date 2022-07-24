#pragma once

#include "Copper/Core/Core.h"

namespace Copper
{
class COPPER_API ScopedDebugTimer
{
public:
    ScopedDebugTimer(const char* name);
    ~ScopedDebugTimer();

    void Stop();

private:
    std::chrono::time_point<std::chrono::steady_clock> m_Start;
    bool m_Stopped = false;
    const char* m_Name;
};

class COPPER_API DebugProfiler
{
public:
    struct EntryData
    {
        std::string Name;
        float Start;
        float End;
        uint32_t ThreadId;
    };

public:
    ~DebugProfiler();

    void BeginSession(const std::string& name);
    void EndSession();

    void WriteEntry(const EntryData& data);

    static void Init();
    static DebugProfiler* Get();

private:
    DebugProfiler() = default;

    void WriteHeader();
    void WriteFooter();

private:
    std::fstream m_File;
    uint32_t m_EntriesCount{ 0 };

    static DebugProfiler* s_Instance;
};

#ifdef CPR_ENABLE_PROFILER
#define CPR_PROFILER_INIT() Copper::DebugProfiler::Init()
#define CPR_PROFILER_START_SESSION(name) Copper::DebugProfiler::Get()->BeginSession(name)
#define CPR_PROFILER_END_SESSION() Copper::DebugProfiler::Get()->EndSession()
#define CPR_PROFILER_TRACE_SCOPE(name) auto dtimer##__LINE__ = Copper::ScopedDebugTimer(name)
#define CPR_PROFILER_TRACE_FUNCTION() auto dtimer##__LINE__ = Copper::ScopedDebugTimer(__FUNCSIG__)
#else
#define CPR_PROFILER_INIT()
#define CPR_PROFILER_START_SESSION(name)
#define CPR_PROFILER_END_SESSION()
#define CPR_PROFILER_TRACE_SCOPE(name)
#define CPR_PROFILER_TRACE_FUNCTION()
#endif

} // namespace Copper
