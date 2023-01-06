#include "FileMime.h"

namespace
{
const char* bmpMime = "image/bmp";
}

namespace Copper::FileMime
{
std::string ToMimeString(Type type)
{
    switch (type)
    {
    case Type::Bmp:
        return bmpMime;

    default:
        return "";
    }
}

Type FromMimeString(const std::string& mime)
{
    if (mime == bmpMime)
        return Type::Bmp;

    return Type::None;
}

} // namespace Copper::FileMime
