#include "FileReadStream.h"

namespace Copper
{

FileReadStream::FileReadStream(const std::filesystem::path& path) : m_Stream(path, std::ifstream::binary) {}

uint64_t FileReadStream::GetPos() { return m_Stream.tellg(); }

bool FileReadStream::IsEof() { return m_Stream.eof(); }

bool FileReadStream::HasError() const
{
    return (m_Stream.fail() && !m_Stream.eof()) || m_Stream.bad() || ReadStreamBase::HasError();
}

uint64_t FileReadStream::ReadChunk(char* buffer, uint64_t size)
{
    m_Stream.read(buffer, size);
    return m_Stream.gcount();
}

} // namespace Copper
