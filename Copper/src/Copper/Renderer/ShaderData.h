#pragma once

#include "Copper/Core.h"

namespace Copper::ShaderData
{

enum Type
{
    Float, Float2, Float3, Float4,
    Int, Int2, Int3, Int4,
    Mat3, Mat4,
    Bool
};

COPPER_API uint32_t GetSize(Type type);
COPPER_API uint32_t GetCount(Type type);

}
