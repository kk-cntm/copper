#pragma once

#include "FileMime.h"

#include <unordered_map>
#include <string>
#include <vector>

namespace Copper
{
struct FileLayout
{
    uint64_t Offset;
    uint64_t WrittenSize;
    uint64_t OriginalSize;
};

struct ParsedFileData
{
    FileMime::Type Mime;
    std::filesystem::path Path;
};

struct FileMeta
{
    FileMime::Type Mime;
    uint64_t CompressedSize;
    uint64_t OriginalSize;
    uint64_t Offset;
    std::string Path;
};

} // namespace Copper
