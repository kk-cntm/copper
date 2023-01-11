#include "BundleDeserializer.h"
#include "context.h"
#include "bundle-sections/versionsection.h"
#include "bundle-sections/metatablesection.h"
#include "bundle-sections/assetssection.h"
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

    VersionSectionReader versionReader(stream);
    const auto& [versionMajor, versionMinor] = versionReader.Read();
    if (versionReader.HasError())
    {
        m_ErrorFlags |= FailedToReadVersion;
        return false;
    }

    m_VersionMajor = versionMajor;
    m_VersionMinor = versionMinor;

    MetaTableSectionReader metatableReader(stream);
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

    const FileMeta& meta = m_Metatable.at(hash);

    char* compressedBlob = (char*)std::malloc(meta.CompressedSize);
    char* blob = (char*)std::malloc(meta.OriginalSize);

    std::ifstream stream(m_BundlePath, std::ifstream::binary);
    stream.seekg(meta.Offset, std::ifstream::beg);
    stream.read(compressedBlob, meta.CompressedSize);

    const auto& [error, fileSize] = AssetsSectionReader::Decompress(compressedBlob, blob, meta.CompressedSize,
                                                                    meta.OriginalSize);

    std::free(compressedBlob);

    CPR_CORE_ASSERT(!error && fileSize == meta.OriginalSize, "File size mismatch before and after compression");

    return MakeRef<Resource>(name, meta.OriginalSize, blob, meta.Mime);
}

} // namespace Copper
