#pragma once

#include "WriteStreamBase.h"

#include <fstream>

namespace Copper
{
/*!
 * \brief FileWriteStream:
 * represents file writer with data processors.
 *
 * Current implementation uses std::ofstream under the hood.
 */
class FileWriteStream : public WriteStreamBase
{
public:
    explicit FileWriteStream(const std::filesystem::path& path);

    virtual inline uint64_t GetPos() override { return m_Stream.tellp(); };
    virtual inline void SeekPos(uint64_t pos) override { m_Stream.seekp(pos, std::ifstream::beg); }
    virtual inline bool IsEof() override { return m_Stream.eof(); }
    virtual bool HasError() const override;

private:
    virtual uint64_t WriteChunk(const char* buffer, uint64_t size) override;

private:
    std::ofstream m_Stream;
};
} // namespace Copper
