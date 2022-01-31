#pragma once

namespace Copper
{
/*!
 * Platform class contains common functions which are depend on platform
 */
class Platform
{
public:
    inline static float GetTime() { return s_Instance->GetTimeImpl(); }

private:
    virtual float GetTimeImpl() const = 0;

    static Platform* s_Instance;
};

}
