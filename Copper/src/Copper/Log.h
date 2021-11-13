#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Copper
{

class Log
{
public:
    static void Init();
    
    static inline std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
    static inline std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    
private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
    
};

// Core log macros
#define CPR_CORE_FATAL(...) ::Copper::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define CPR_CORE_ERROR(...) ::Copper::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CPR_CORE_WARN(...) ::Copper::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CPR_CORE_INFO(...) ::Copper::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CPR_CORE_TRACE(...) ::Copper::Log::GetCoreLogger()->trace(__VA_ARGS__)

// Client log macros
#define CPR_FATAL(...) ::Copper::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define CPR_ERROR(...) ::Copper::Log::GetClientLogger()->error(__VA_ARGS__)
#define CPR_WARN(...) ::Copper::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CPR_INFO(...) ::Copper::Log::GetClientLogger()->info(__VA_ARGS__)
#define CPR_TRACE(...) ::Copper::Log::GetClientLogger()->trace(__VA_ARGS__)

}
