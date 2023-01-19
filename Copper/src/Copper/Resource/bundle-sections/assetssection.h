#pragma once

#include "Copper/Resource/context.h"
#include "Copper/Core/io/FileWriteStream.h"

namespace Copper
{

/*!
 * \brief AssetsSectionWriter:
 * writes down listed assets into bundle file.
 */
class AssetsSectionWriter
{
public:
    AssetsSectionWriter(FileWriteStream& stream, const std::filesystem::path& workingDir);

    bool Write(const std::vector<ParsedFileData>& files);
    const std::map<std::string, FileLayout>& GetFilesLayout() const;

private:
    std::map<std::string, FileLayout> m_FilesLayout;
    const std::filesystem::path m_WorkingDir;
    FileWriteStream& m_Stream;
};

/*!
 * \brief AssetsSectionReader:
 * namespace for the staff realted to assets reading
 */
class AssetsSectionReader
{
public:
    static std::pair<int, uint64_t> Decompress(char* source, char* dest, uint64_t sourceSize, uint64_t destSize);
};
} // namespace Copper
