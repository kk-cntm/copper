#include "ShaderData.h"
#include "Copper/Log.h"

namespace Copper::ShaderData
{

uint32_t GetSize(Type type)
{
    switch (type) {
    case Type::Float:    return sizeof(float);
    case Type::Float2:   return sizeof(float) * 2;
    case Type::Float3:   return sizeof(float) * 3;
    case Type::Float4:   return sizeof(float) * 4;
    case Type::Int:      return sizeof(int32_t);
    case Type::Int2:     return sizeof(int32_t) * 2;
    case Type::Int3:     return sizeof(int32_t) * 3;
    case Type::Int4:     return sizeof(int32_t) * 4;
    case Type::Mat3:     return sizeof(float) * 3 * 3;
    case Type::Mat4:     return sizeof(float) * 4 * 4;
    case Type::Bool:     return sizeof(bool);
    }

    CPR_CORE_ASSERT(false, "Unhandled ShaderData::Type");
    return 0;
}

uint32_t GetCount(Type type)
{
    switch (type) {
    case Type::Float:    return 1;
    case Type::Float2:   return 2;
    case Type::Float3:   return 3;
    case Type::Float4:   return 4;
    case Type::Int:      return 1;
    case Type::Int2:     return 2;
    case Type::Int3:     return 3;
    case Type::Int4:     return 4;
    case Type::Mat3:     return 3 * 3;
    case Type::Mat4:     return 4 * 4;
    case Type::Bool:     return 1;
    }

    CPR_CORE_ASSERT(false, "Unhandled ShaderData::Type");
    return 0;
}

}
