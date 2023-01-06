#pragma once

#include "FileMime.h"

#include <unordered_map>
#include <string>
#include <vector>

namespace Copper
{
struct ParsedFileData
{
    FileMime::Type Mime;
    std::string Path;
};

struct FileMeta
{
    FileMime::Type Mime;
    uint64_t Size;
    uint64_t Offset;
    std::string Path;
};

struct BundleReadContext
{
    uint32_t VersionMajor{ 0 };
    uint32_t VersionMinor{ 0 };
    std::unordered_map<uint64_t, FileMeta> Metatable;
};

struct BundleWriteContext
{
    uint32_t VersionMajor;
    uint32_t VersionMinor;
    std::vector<ParsedFileData> ParsedFilesData;
};

} // namespace Copper
