#include "hash.h"
#include "siphash.h"

#include <cstring>

namespace Copper
{
uint64_t getHash(const char* str)
{
    static constexpr uint64_t key = 0x99BAE564988696AF;
    uint64_t result{ 0 };

    siphash(str, std::strlen(str), &key, (uint8_t*)&result, sizeof(result));

    return result;
}

} // namespace Copper