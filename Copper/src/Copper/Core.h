#pragma once

#define BIT(x) (1 << x)

#ifdef CPR_ENABLE_ASSERTS
    #define CPR_ASSERT(x, ...) {\
        if(!(x)) {\
            CPR_ERROR("Assertion failed: {0}", __VA_ARGS__);\
            __builtin_trap();\
        }\
    }
    #define CPR_CORE_ASSERT(x, ...) {\
        if(!(x)) {\
            CPR_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__);\
            __builtin_trap();\
        }\
    }
#else
    #define CPR_ASSERT
    #define CPR_CORE_ASSERT
#endif
