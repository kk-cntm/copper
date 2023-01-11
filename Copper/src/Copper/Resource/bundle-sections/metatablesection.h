#pragma once

#include "Copper/Resource/context.h"

namespace Copper
{
/*!
 * \brief MetaTableSectionWriter:
 * writes metatable to bundle file from \param context
 */
class MetaTableSectionWriter
{
public:
    explicit MetaTableSectionWriter(std::ofstream& stream, const std::filesystem::path& workingDir);

    bool Write(const std::vector<ParsedFileData>& files, const std::map<std::string, FileLayout>& filesLayout);

    static uint32_t CalculateMetadataSize(const std::vector<ParsedFileData>& parsedFilesData);

private:
    std::ofstream& m_Stream;
    std::filesystem::path m_WorkingDir;
};

/*!
 * \brief MetaTableSectionReader:
 * reads metatable from bundle file into \param context
 */
class MetaTableSectionReader
{
public:
    explicit MetaTableSectionReader(std::ifstream& stream);

    std::unordered_map<uint64_t, FileMeta> Read();
    inline bool HasError() const { return m_Error; }

private:
    std::ifstream& m_Stream;
    bool m_Error{ false };
};
} // namespace Copper
