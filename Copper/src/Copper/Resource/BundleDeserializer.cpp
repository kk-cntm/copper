#include "BundleDeserializer.h"
#include "bundle-sections/versionsection.h"
#include "bundle-sections/metatablesection.h"
#include "Copper/Core/hash.h"
#include "Copper/Debug/DebugProfiler.h"

namespace Copper
{
BundleDeserializer::BundleDeserializer(const std::filesystem::path& bundlePath) : m_BundlePath(bundlePath) {}

bool BundleDeserializer::Deserialize()
{
    CPR_PROFILER_TRACE_SCOPE("Deserialize bundle: ");

    std::ifstream stream(m_BundlePath, std::ifstream::binary);

    VersionSectionReader versionReader(stream);
    const auto& [versionMajor, versionMinor] = versionReader.Read();
    if (versionReader.HasError())
    {
        m_ErrorFlags |= FailedToReadVersion;
        return false;
    }

    m_VersionMajor = versionMajor;
    m_VersionMinor = versionMinor;

    MetaTableSectionReader metatableReader(stream, m_BundlePath);
    m_Metatable = metatableReader.Read();
    if (metatableReader.HasError())
    {
        m_ErrorFlags |= FailedToReadMetatable;
        return false;
    }

    return true;
}

Ref<Resource> BundleDeserializer::GetResource(const std::string& name) const
{
    const uint64_t hash = getHash(name.c_str());
    if (m_Metatable.find(hash) == m_Metatable.cend())
        return nullptr;

    return m_Metatable.at(hash);
}

} // namespace Copper
