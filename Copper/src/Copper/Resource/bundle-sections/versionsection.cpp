#include "versionsection.h"
#include "cprpch.h"
#include "Copper/Core/Log.h"

namespace Copper
{
VersionSectionWriter::VersionSectionWriter(std::ofstream& stream) : m_Stream(stream) {}

bool VersionSectionWriter::Write(uint32_t major, uint32_t minor)
{
    m_Stream.write((char*)&major, sizeof(major));
    if (m_Stream.bad() || m_Stream.fail())
    {
        CPR_CORE_WARN("Failed to write major version: {0}", std::strerror(errno));
        return false;
    }

    m_Stream.write((char*)&minor, sizeof(minor));
    if (m_Stream.bad() || m_Stream.fail())
    {
        CPR_CORE_WARN("Failed to write minor version: {0}", std::strerror(errno));
        return false;
    }

    return true;
}

VersionSectionReader::VersionSectionReader(std::ifstream& stream) : m_Stream(stream) {}

std::pair<uint32_t, uint32_t> VersionSectionReader::Read()
{
    uint32_t versionMajor;
    uint32_t versionMinor;

    m_Error = false;

    m_Stream.read((char*)&versionMajor, sizeof(versionMajor));
    if (m_Stream.gcount() != sizeof(versionMajor))
    {
        m_Error = true;
        CPR_CORE_WARN("Failed to read major version: {0}", std::strerror(errno));
        return { 0, 0 };
    }

    m_Stream.read((char*)&versionMinor, sizeof(versionMinor));
    if (m_Stream.gcount() != sizeof(versionMinor))
    {
        m_Error = true;
        CPR_CORE_WARN("Failed to read minor version: {0}", std::strerror(errno));
        return { 0, 0 };
    }

    return { versionMajor, versionMinor };
}

} // namespace Copper
