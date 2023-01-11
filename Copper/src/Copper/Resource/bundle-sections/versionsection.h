#pragma once

#include <stdint.h>
#include <iosfwd>
#include <utility>

namespace Copper
{
/*!
 * \brief VersionSectionWriter:
 * writes version into bundle file
 */
class VersionSectionWriter
{
public:
    explicit VersionSectionWriter(std::ofstream& stream);

    bool Write(uint32_t major, uint32_t minor);

private:
    std::ofstream& m_Stream;
};

/*!
 * \brief VersionSectionReader:
 * reads version from bundle file
 */
class VersionSectionReader
{
public:
    explicit VersionSectionReader(std::ifstream& stream);

    std::pair<uint32_t, uint32_t> Read();
    inline bool HasError() const { return m_Error; };

private:
    std::ifstream& m_Stream;
    bool m_Error{ false };
};

} // namespace Copper
