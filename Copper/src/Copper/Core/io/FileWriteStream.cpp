#include "FileWriteStream.h"

namespace Copper
{

FileWriteStream::FileWriteStream(const std::filesystem::path& path) : m_Stream(path, std::ifstream::binary) {}

bool FileWriteStream::HasError() const
{
    return (m_Stream.fail() && !m_Stream.eof()) || m_Stream.bad() || WriteStreamBase::HasError();
}

uint64_t FileWriteStream::WriteChunk(const char* buffer, uint64_t size)
{
    const uint64_t pos = GetPos();
    m_Stream.write(buffer, size);
    return GetPos() - pos;
}

} // namespace Copper
