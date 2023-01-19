#include "ZlibCompresser.h"

#include "Copper/Core/Log.h"

namespace Copper
{
ZlibCompresser::ZlibCompresser()
{
    m_ZlibStream.zalloc = Z_NULL;
    m_ZlibStream.zfree = Z_NULL;
    m_ZlibStream.opaque = Z_NULL;

    if (deflateInit(&m_ZlibStream, Z_DEFAULT_COMPRESSION) != Z_OK)
    {
        EndDeflate();
        CPR_CORE_WARN("Failed to init zlib");
    }
}

ZlibCompresser::~ZlibCompresser() { EndDeflate(); }

uint64_t ZlibCompresser::Process(const char* fromBuffer, uint64_t fromSize, char* toBuffer, uint64_t toSize,
                                 bool lastChunk)
{
    m_ZlibStream.avail_in = fromSize;
    m_ZlibStream.next_in = (unsigned char*)fromBuffer;

    m_ZlibStream.avail_out = toSize;
    m_ZlibStream.next_out = reinterpret_cast<unsigned char*>(toBuffer);

    if (deflate(&m_ZlibStream, lastChunk ? Z_FINISH : Z_NO_FLUSH) == Z_STREAM_ERROR)
    {
        CPR_CORE_WARN("Unable to compress chunk");
        deflateEnd(&m_ZlibStream);
        m_Error = true;

        return 0;
    }

    if (lastChunk)
        EndDeflate();

    return toSize - m_ZlibStream.avail_out;
}

void ZlibCompresser::EndDeflate()
{
    if (!m_IsEnded)
    {
        deflateEnd(&m_ZlibStream);
        m_IsEnded = true;
    }
}
} // namespace Copper
