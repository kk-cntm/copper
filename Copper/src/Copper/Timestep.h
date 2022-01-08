#pragma once

#include "Copper/Core.h"

namespace Copper
{

class COPPER_API Timestep
{
public:
    Timestep(float time = 0.0f) : m_Time(time) {};

    inline float GetSeconds() { return m_Time; }
    inline float GetMilliseconds() { return m_Time * 1000.0f; }

    inline operator float() { return m_Time; }

private:
    float m_Time;
};

}
