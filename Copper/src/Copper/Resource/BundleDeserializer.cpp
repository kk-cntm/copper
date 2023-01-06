#include "BundleDeserializer.h"
#include "context.h"
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

    std::ifstream stream;
    stream.open(m_BundlePath, std::ifstream::binary);

    readVersionSection(stream, m_ReadContext);
    readMetaTableSection(stream, m_ReadContext);

    return true;
}

Ref<Resource> BundleDeserializer::GetResource(const std::string& name) const
{
    const uint64_t hash = getHash(name.c_str());
    if (m_ReadContext.Metatable.find(hash) == m_ReadContext.Metatable.cend())
        return nullptr;

    const FileMeta& meta = m_ReadContext.Metatable.at(hash);

    char* blob = (char*)std::malloc(meta.Size);

    std::ifstream stream(m_BundlePath, std::ifstream::binary);
    stream.seekg(meta.Offset, std::ifstream::beg);
    stream.read(blob, meta.Size);

    return MakeRef<Resource>(name, meta.Size, blob, meta.Mime);
}

} // namespace Copper
