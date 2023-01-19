#include "assetssection.h"
#include "Copper/Core/Log.h"
#include "Copper/Core/io/FileReadStream.h"
#include "Copper/Core/io/ZlibCompresser.h"
#include "Copper/Core/io/FileWriteStream.h"

#include <zlib.h>

namespace
{
const uint64_t COMPRESSING_CHUNK_SIZE = 1024 * 256;
} // namespace

namespace Copper
{
AssetsSectionWriter::AssetsSectionWriter(FileWriteStream& stream, const std::filesystem::path& workingDir)
    : m_Stream(stream), m_WorkingDir(workingDir)
{
}

bool AssetsSectionWriter::Write(const std::vector<ParsedFileData> &files)
{
    const uint64_t bufferSize = 1024 * 128;
    auto buffer = MakeScoped<char[]>(bufferSize);

    for (const auto& fileData : files)
    {
        const std::filesystem::path filePath = m_WorkingDir / fileData.Path;

        FileReadStream reader(filePath);

        const auto zlibProcessor = MakeRef<ZlibCompresser>();
        m_Stream.AddDataProcessor(zlibProcessor);

        const uint64_t prevWriterPos = m_Stream.GetPos();
        const uint64_t prevReaderPos = reader.GetPos();

        uint64_t totalBytesRead = 0;
        uint64_t totalBytesWritten = 0;
        while (!reader.IsEof())
        {
            const uint64_t bytesRead = reader.Read(buffer.get(), bufferSize);
            if (reader.HasError())
            {
                CPR_CORE_WARN("Failed to read chunk at {} pos", reader.GetPos());
                return false;
            }

            totalBytesRead += bytesRead;
            totalBytesWritten += m_Stream.Write(buffer.get(), bytesRead, reader.IsEof());

            if (m_Stream.HasError())
            {
                CPR_CORE_WARN("Failed to write chunk at {} pos", m_Stream.GetPos());
                return false;
            }
        }

        m_Stream.DeleteDataProcessor(zlibProcessor);

        FileLayout layout;
        layout.Offset = prevWriterPos;
        layout.OriginalSize = totalBytesRead;
        layout.WrittenSize = totalBytesWritten;

        m_FilesLayout[fileData.Path] = layout;
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
