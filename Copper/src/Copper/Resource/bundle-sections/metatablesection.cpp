#include "metatablesection.h"
#include "Copper/Core/hash.h"

namespace // helpers
{
uint32_t calculateMetadataSize(const std::vector<Copper::ParsedFileData>& parsedFilesData)
{
    uint32_t size = 0;

    for (const auto& file : parsedFilesData)
    {
        // hash
        size += sizeof(uint64_t);

        // path section
        size += std::strlen(file.Path.c_str()) + 1;

        // mime section
        size += sizeof(Copper::FileMime::Type);

        // blob size section
        size += sizeof(uint64_t);

        // blob offset
        size += sizeof(uint64_t);
    }

    return size;
}
} // namespace

namespace Copper
{
void readMetaTableSection(std::ifstream& stream, BundleReadContext& context)
{
    uint32_t metadataSize = 0;
    stream.read((char*)&metadataSize, sizeof(metadataSize));

    char* metadata = (char*)std::malloc(metadataSize);
    stream.read(metadata, metadataSize);

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

        meta.Size = *((uint64_t*)dataPtr);
        dataPtr += sizeof(meta.Size);

        meta.Offset = *((uint64_t*)dataPtr);
        dataPtr += sizeof(meta.Offset);

        context.Metatable[hash] = meta;
    }
}

void writeMetaTableSection(std::ofstream& stream, BundleWriteContext& context, const std::filesystem::path& dir)
{
    const uint32_t metadataSize = calculateMetadataSize(context.ParsedFilesData);
    stream.write((char*)&metadataSize, sizeof(metadataSize));

    uint64_t fileOffset = static_cast<uint64_t>(stream.tellp()) + metadataSize;

    for (const auto& fileMeta : context.ParsedFilesData)
    {
        const uint64_t hash = getHash(fileMeta.Path.c_str());
        stream.write((char*)&hash, sizeof(hash));

        stream.write(fileMeta.Path.c_str(), fileMeta.Path.length() + 1);
        stream.write((char*)&fileMeta.Mime, sizeof(fileMeta.Mime));

        uint64_t fileSize = std::filesystem::file_size(std::filesystem::path(dir.string() + '/' + fileMeta.Path));
        stream.write((char*)&fileSize, sizeof(fileSize));

        stream.write((char*)&fileOffset, sizeof(fileOffset));

        fileOffset += fileSize;
    }
}

} // namespace Copper
