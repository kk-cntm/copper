#pragma once

#include "Copper/Core/Core.h"
#include "BundleDeserializer.h"
#include "Resource.h"

namespace Copper
{
class COPPER_API Rms
{
public:
    /*!
     * \brief Rms::GetResource:
     * \returns resource for given \param name
     *
     * If the resource isn't preloaded it will load it in the same thread.
     * This function is safe for multithreding.
     * If the resource is loaded from disk, it will stored in cache similar to \b Rms::PreloadAll
     *
     * \param name - the name of the resource. Should have the following signature: bundleId:fileName
     *
     */
    inline static Ref<Resource> GetResource(const std::string& name) { return s_Rms->GetResourceImpl(name); }

    /*!
     * \brief Rms::PreloadAll:
     * preloads given set of resources into RAM. Further on can be retrieved from \b Rms::GetResource
     *
     * \param paths - files in the following signature bundleId:fileName
     */
    inline static void PreloadAll(const std::vector<std::string>& paths) { s_Rms->PreloadAllImpl(paths); }

    /*!
     * \brief Rms::UnloadAll:
     * unloads all preloaded resources from RAM.
     */
    inline static void UnloadAll() { s_Rms->UnloadAllImpl(); };

    /*!
     * \brief Rms::UnloadAll:
     * unloads give files from RAM.
     *
     * \param paths - files to be unloaded
     */
    inline static void UnloadAll(const std::vector<std::string>& paths) { s_Rms->UnloadAllImpl(paths); }

    inline static void OnUpdate(){ s_Rms->OnUpdateImpl(); };

    /*!
     * \brief Rms::Init:
     * initializes resource managements system from given bundles.
     * Should be called on engine startup.
     *
     * \param bundles - bundles to be loaded
     */
    static void Init(const std::vector<const char*>& bundles);

private:
    Ref<Resource> GetResourceImpl(const std::string& name);
    void PreloadAllImpl(const std::vector<std::string>& paths);
    void UnloadAllImpl();
    void UnloadAllImpl(const std::vector<std::string>& paths);
    void OnUpdateImpl();

    Ref<Resource> LoadFile(const std::string& path);
    void OnFilesLoadingComplete();

private:
    std::unordered_map<std::string, Ref<BundleDeserializer>> m_Bundles;
    std::unordered_map<std::string, Ref<Resource>> m_Preloaded;
    std::map<std::string, std::future<Ref<Resource>>> m_LoadHandles;
    std::mutex m_PreloadedMutex;

private:
    static Ref<Rms> s_Rms;
};

} // namespace Copper
