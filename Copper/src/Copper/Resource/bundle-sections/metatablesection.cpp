#include "metatablesection.h"
#include "Copper/Core/hash.h"
#include "Copper/Core/Log.h"

namespace Copper
{
MetaTableSectionWriter::MetaTableSectionWriter(std::ofstream& stream, const std::filesystem::path& workingDir)
    : m_Stream(stream), m_WorkingDir(workingDir)
{
}

bool MetaTableSectionWriter::Write(const std::vector<ParsedFileData>& files, const std::map<std::string, FileLayout>& filesLayout)
{
    CPR_CORE_ASSERT(files.size() == filesLayout.size(), "files and filesLayout size mismatch");
    const uint32_t metadataSize = CalculateMetadataSize(files);
    m_Stream.write((char*)&metadataSize, sizeof(metadataSize));

    for (const auto& fileData : files)
    {
        const auto fileLayout = filesLayout.at(fileData.Path);

        const uint64_t hash = getHash(fileData.Path.c_str());
        m_Stream.write((char*)&hash, sizeof(hash));
        if (m_Stream.bad() || m_Stream.fail())
        {
            CPR_CORE_WARN("Failed to write hash for {0}", fileData.Path);
            return false;
        }

        m_Stream.write(fileData.Path.c_str(), fileData.Path.string().length() + 1);
        if (m_Stream.bad() || m_Stream.fail())
        {
            CPR_CORE_WARN("Failed to write file name for {0}", fileData.Path);
            return false;
        }

        m_Stream.write((char*)&fileData.Mime, sizeof(fileData.Mime));
        if (m_Stream.bad() || m_Stream.fail())
        {
            CPR_CORE_WARN("Failed to write file mime for {0}", fileData.Path);
            return false;
        }

        m_Stream.write((char*)&fileLayout.WrittenSize, sizeof(fileLayout.WrittenSize));
        if (m_Stream.bad() || m_Stream.fail())
        {
            CPR_CORE_WARN("Failed to write file compressed size for {0}", fileData.Path);
            return false;
        }

        m_Stream.write((char*)&fileLayout.OriginalSize, sizeof(fileLayout.OriginalSize));
        if (m_Stream.bad() || m_Stream.fail())
        {
            CPR_CORE_WARN("Failed to write original file size for {0}", fileData.Path);
            return false;
        }

        m_Stream.write((char*)&fileLayout.Offset, sizeof(fileLayout.Offset));
        if (m_Stream.bad() || m_Stream.fail())
        {
            CPR_CORE_WARN("Failed to write file offset for {0}", fileData.Path);
            return false;
        }
    }

    return true;
}

uint32_t MetaTableSectionWriter::CalculateMetadataSize(const std::vector<ParsedFileData>& parsedFilesData)
{
    uint32_t size = 0;

    // metatable overall size
    size += sizeof(uint32_t);

    for (const auto& fileData : parsedFilesData)
    {
        // hash
        size += sizeof(uint64_t);

        // path section
        size += std::strlen(fileData.Path.c_str()) + 1;

        // mime section
        size += sizeof(Copper::FileMime::Type);

        // blob size section
        size += sizeof(uint64_t);

        // blob original size
        size += sizeof(uint64_t);

        // blob offset
        size += sizeof(uint64_t);
    }

    return size;
}

MetaTableSectionReader::MetaTableSectionReader(std::ifstream& stream) : m_Stream(stream) {}

std::unordered_map<uint64_t, FileMeta> MetaTableSectionReader::Read()
{
    std::unordered_map<uint64_t, FileMeta> result;

    m_Error = false;

    uint32_t metadataSize = 0;
    m_Stream.read((char*)&metadataSize, sizeof(metadataSize));

    if (m_Stream.gcount() != sizeof(metadataSize))
    {
        m_Error = true;
        return {};
    }

    char* metadata = (char*)std::malloc(metadataSize);
    m_Stream.read(metadata, metadataSize);

    if (metadataSize != m_Stream.gcount())
    {
        m_Error = true;
        CPR_CORE_WARN("");
        return {};
    }

    char* dataPtr = metadata;
    while (dataPtr < metadata + metadataSize)
    {
        FileMeta meta;

        const uint64_t hash = *((uint64_t*)dataPtr);
        dataPtr += sizeof(hash);

        meta.Path = dataPtr;
        dataPtr += std::strlen(dataPtr) + 1;

        meta.Mime = (FileMime::Type)(*dataPtr);
        dataPtr += sizeof(meta.Mime);

        meta.CompressedSize = *((uint64_t*)dataPtr);
        dataPtr += sizeof(meta.CompressedSize);

        meta.OriginalSize = *((uint64_t*)dataPtr);
        dataPtr += sizeof(meta.OriginalSize);

        meta.Offset = *((uint64_t*)dataPtr);
        dataPtr += sizeof(meta.Offset);

        result[hash] = meta;
    }

    return result;
}

} // namespace Copper