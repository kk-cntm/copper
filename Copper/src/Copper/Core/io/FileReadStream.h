#pragma once

#include "ReadStreamBase.h"

#include <filesystem>
#include <fstream>

namespace Copper
{
/*!
 * \brief FileReadStream:
 * represents file reader with data processors.
 *
 * Current implementation uses std::ifstream under the hood.
 */
class FileReadStream : public ReadStreamBase
{
public:
    FileReadStream(const std::filesystem::path& path);

    uint64_t GetPos() override;
    bool IsEof() override;
    bool HasError() const override;

private:
    uint64_t ReadChunk(char* buffer, uint64_t size) override;

private:
    std::ifstream m_Stream;
};
} // namespace Copper
