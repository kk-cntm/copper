#include "DebugProfiler.h"

#include <sstream>

namespace Copper
{
ScopedDebugTimer::ScopedDebugTimer(const char* name) : m_Start(std::chrono::high_resolution_clock::now()), m_Name(name)
{
}

ScopedDebugTimer::~ScopedDebugTimer()
{
    if (!m_Stopped)
        Stop();
}

void ScopedDebugTimer::Stop()
{
    float end = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now())
                    .time_since_epoch()
                    .count()
                * 0.001;
    float start = std::chrono::time_point_cast<std::chrono::microseconds>(m_Start).time_since_epoch().count() * 0.001;

    uint32_t threadId = std::hash<std::thread::id>{}(std::this_thread::get_id());

    m_Stopped = true;
    DebugProfiler::Get()->WriteEntry({ m_Name, start, end, threadId });
}

// DebugProfiler

DebugProfiler* DebugProfiler::s_Instance = nullptr;

DebugProfiler::~DebugProfiler() { m_File.close(); }

void DebugProfiler::BeginSession(const std::string& name)
{
    m_File.open("Profiler-" + name + ".json", std::ios::out | std::ios::trunc);
    WriteHeader();
}

void DebugProfiler::EndSession()
{
    WriteFooter();
    m_File.close();
}

void DebugProfiler::WriteEntry(const EntryData& data)
{
    std::stringstream ss;

    if (m_EntriesCount++ > 0)
        ss << ",";

    ss << "{";
    ss << "\"cat\":"
       << "\"function\",";
    ss << "\"dur\":" << (data.End - data.Start) << ",";
    ss << "\"name\":"
       << "\"" << data.Name << "\",";
    ss << "\"ph\":"
       << "\"X\",";
    ss << "\"pid\":"
       << "0,";
    ss << "\"tid\":" << data.ThreadId << ",";
    ss << "\"ts\":" << data.Start;
    ss << "}";

    m_File << ss.str();
    m_File.flush();
}

void DebugProfiler::Init()
{
    if (!s_Instance)
        s_Instance = new DebugProfiler;
}

void DebugProfiler::WriteHeader()
{
    m_File << "{\"otherData\":{},\"traceEvents\":[";
    m_File.flush();
}

void DebugProfiler::WriteFooter()
{
    m_File << "]}";
    m_File.flush();
}

DebugProfiler* DebugProfiler::Get() { return s_Instance; }

} // namespace Copper
