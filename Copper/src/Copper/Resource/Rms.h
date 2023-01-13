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
     * \brief Rms::Init:
     * initializes resource managements system from given bundles.
     * Should be called on engine startup.
     *
     * \param bundles - bundles to be loaded
     */
    static void Init(const std::vector<const char*>& bundles);

private:
    Ref<Resource> GetResourceImpl(const std::string& name);

private:
    std::unordered_map<std::string, Ref<BundleDeserializer>> m_Bundles;

private:
    static Ref<Rms> s_Rms;
};

} // namespace Copper
