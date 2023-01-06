#pragma once

#include "Log.h"

#include <memory>

#define BIT(x) (1 << x)

#ifdef CPR_ENABLE_ASSERTS
#define CPR_ASSERT(x, ...)                                                                                             \
    {                                                                                                                  \
        if (!(x))                                                                                                      \
        {                                                                                                              \
            CPR_ERROR("Assertion failed: {0}", __VA_ARGS__);                                                           \
            __builtin_trap();                                                                                          \
        }                                                                                                              \
    }
#define CPR_CORE_ASSERT(x, ...)                                                                                        \
    {                                                                                                                  \
        if (!(x))                                                                                                      \
        {                                                                                                              \
            CPR_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__);                                                      \
            __builtin_trap();                                                                                          \
        }                                                                                                              \
    }
#else
#define CPR_ASSERT
#define CPR_CORE_ASSERT
#endif

#define CPR_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#ifdef CPR_PLATFORM_MACOS
#define COPPER_API __attribute__((visibility("default")))
#else
#define COPPER_API
#endif

namespace Copper
{

template <typename T>
using Scoped = std::unique_ptr<T>;

template <typename T, typename... Params>
inline Scoped<T> MakeScoped(Params&&... args)
{
    return std::make_unique<T>(std::forward<Params>(args)...);
}
template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename... Params>
inline Ref<T> MakeRef(Params&&... args)
{
    return std::make_shared<T>(std::forward<Params>(args)...);
}

} // namespace Copper
