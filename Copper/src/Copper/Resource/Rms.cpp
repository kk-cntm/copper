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

    const auto cachedIt = m_Preloaded.find(name);
    if (cachedIt != m_Preloaded.cend())
        return (*cachedIt).second;

    const auto& [bundleName, fileName] = parseFilePath(name);

    if (bundleName.empty() || fileName.empty())
        return nullptr;

    const auto bundleIt = m_Bundles.find(bundleName);
    if (bundleIt == m_Bundles.cend())
        return nullptr;

    const auto resource = (*bundleIt).second->GetResource(fileName);
    m_Preloaded[name] = resource;

    return resource;
}

void Rms::PreloadAllImpl(const std::vector<std::string>& paths)
{
    for (const auto& path : paths)
    {
        if (m_Preloaded.find(path) != m_Preloaded.end())
            continue;

        m_LoadHandles[path] = std::async(std::launch::async, &Rms::LoadFile, this, path);
    }
}

void Rms::UnloadAllImpl() { m_Preloaded.clear(); }

void Rms::UnloadAllImpl(const std::vector<std::string>& paths)
{
    for (const auto& path : paths)
        m_Preloaded.erase(path);
}

void Rms::OnUpdateImpl()
{
    CPR_PROFILER_TRACE_FUNCTION();

    std::vector<std::map<std::string, std::future<Ref<Resource>>>::iterator> iteratorsToDelete;
    for (auto it = m_LoadHandles.begin(); it != m_LoadHandles.end(); ++it)
    {
        auto& [_, task] = *it;

        const bool isCompleted = task.wait_for(std::chrono::seconds(0))
                                 == std::future_status::ready;

        if (isCompleted)
        {
            const auto resource = task.get();
            m_Preloaded[resource->GetName()] = resource;
            iteratorsToDelete.push_back(it);
        }
    }

    for (const auto it : iteratorsToDelete)
        m_LoadHandles.erase(it);
}

Ref<Resource> Rms::LoadFile(const std::string& path)
{
    const auto& [bundleName, fileName] = parseFilePath(path);

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
