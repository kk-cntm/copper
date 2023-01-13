#include "cprpch.h"
#include "Rms.h"
#include "Copper/Resource/Resource.h"
#include "Copper/Debug/DebugProfiler.h"

namespace // helpers
{
std::pair<std::string, std::string> parseFilePath(const std::string& path)
{
    const int pos = path.find_first_of(":");
    if (pos == -1)
        return { "", "" };

    return { path.substr(0, pos), path.substr(pos) };
}
} // namespace

namespace Copper
{
Ref<Resource> Rms::GetResourceImpl(const std::string& name)
{
    CPR_PROFILER_TRACE_SCOPE("Load Resource");

    const auto& [bundleName, fileName] = parseFilePath(name);

    if (bundleName.empty() || fileName.empty())
        return nullptr;

    const auto bundleIt = m_Bundles.find(bundleName);
    if (bundleIt == m_Bundles.cend())
        return nullptr;

    return (*bundleIt).second->GetResource(fileName);
}

void Rms::Init(const std::vector<const char*>& bundles)
{
    CPR_PROFILER_TRACE_FUNCTION();
    if (s_Rms)
    {
        CPR_CORE_ERROR("Resource management system has already been initialized");
        return;
    }

    s_Rms = MakeRef<Rms>();

    for (const char* name : bundles)
    {
        const auto deserializer = MakeRef<BundleDeserializer>(name);
        deserializer->Deserialize();

        s_Rms->m_Bundles[name] = deserializer;
    }
}

Ref<Rms> Rms::s_Rms;

} // namespace Copper
