#include "assetssection.h"
#include "Copper/Core/Log.h"

#include <zlib.h>

namespace
{
const uint64_t COMPRESSING_CHUNK_SIZE = 1024 * 256;
} // namespace

namespace Copper
{
AssetsSectionWriter::AssetsSectionWriter(std::ofstream& stream, const std::filesystem::path& workingDir)
    : m_Stream(stream), m_WorkingDir(workingDir)
{
}

bool AssetsSectionWriter::Write(const std::vector<ParsedFileData> &files)
{
    auto originalFileBuffer = MakeScoped<char[]>(COMPRESSING_CHUNK_SIZE);
    auto compressingBuffer = MakeScoped<char[]>(COMPRESSING_CHUNK_SIZE);

    for (const auto& fileData : files)
    {
        const std::filesystem::path filePath = m_WorkingDir / fileData.Path;

        std::ifstream bundleFileStream(filePath, std::ios::binary | std::ios::in);

        bundleFileStream.seekg(0, std::ifstream::end);
        const uint64_t fileSize = bundleFileStream.tellg();
        bundleFileStream.seekg(0, std::ifstream::beg);

        const uint64_t fileOffset = m_Stream.tellp();

        z_stream strm;
        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;

        if (deflateInit(&strm, Z_DEFAULT_COMPRESSION) != Z_OK)
        {
            deflateEnd(&strm);
            CPR_CORE_WARN("Unable to compress file {0}", filePath.string());
            return false;
        }

        uint64_t bytesWrittenCount = 0;
        while (!bundleFileStream.eof())
        {
            bundleFileStream.read(originalFileBuffer.get(), COMPRESSING_CHUNK_SIZE);
            const auto fileChunkReadBytesCount = bundleFileStream.gcount();

            if (!fileChunkReadBytesCount)
            {
                CPR_CORE_WARN("Failed to read data from original file {0}", filePath.string());
                deflateEnd(&strm);
                return false;
            }

            strm.avail_in = fileChunkReadBytesCount;
            strm.next_in = reinterpret_cast<unsigned char*>(originalFileBuffer.get());

            strm.avail_out = COMPRESSING_CHUNK_SIZE;
            strm.next_out = reinterpret_cast<unsigned char*>(compressingBuffer.get());

            if (deflate(&strm, bundleFileStream.eof() ? Z_FINISH : Z_NO_FLUSH) == Z_STREAM_ERROR)
            {
                CPR_CORE_WARN("Unable to compress file {0}", filePath.string());
                deflateEnd(&strm);
                return false;
            }

            m_Stream.write(compressingBuffer.get(), COMPRESSING_CHUNK_SIZE - strm.avail_out);
            if (m_Stream.bad() || m_Stream.fail())
            {
                CPR_CORE_WARN("Failed to write compressed data to the bundle {0}", filePath.string());
                deflateEnd(&strm);
                return false;
            }

            bytesWrittenCount += COMPRESSING_CHUNK_SIZE - strm.avail_out;
        }

        deflateEnd(&strm);

        m_FilesLayout[fileData.Path] = { fileOffset, bytesWrittenCount, fileSize };
    }

    return true;
}

const std::map<std::string, FileLayout>& AssetsSectionWriter::GetFilesLayout() const { return m_FilesLayout; }

std::pair<int, uint64_t> AssetsSectionReader::Decompress(char *source, char *dest, uint64_t sourceSize, uint64_t destSize)
{
    int error;

    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = Z_NULL;
    strm.next_in = Z_NULL;

    error = inflateInit(&strm);
    if (error != Z_OK)
    {
        inflateEnd(&strm);
        return { error, 0 };
    }

    strm.avail_in = sourceSize;
    strm.next_in = (unsigned char*)source;

    strm.avail_out = destSize;
    strm.next_out = (unsigned char*)dest;

    error = inflate(&strm, Z_NO_FLUSH);

    const auto inflateErrors = { Z_STREAM_ERROR, Z_DATA_ERROR, Z_MEM_ERROR };
    if (std::find(inflateErrors.begin(), inflateErrors.end(), error) != inflateErrors.end())
    {
        inflateEnd(&strm);
        return { error, 0 };
    }

    inflateEnd(&strm);

    return { 0, destSize - strm.avail_out };
}

} // namespace Copper
