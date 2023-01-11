#pragma once

#include "context.h"
#include "Resource.h"
#include "Copper/Core/Core.h"

namespace Copper
{
/*!
 * \brief BundleDeserializer:
 * operates over resource bundle file, makes deserialization of metadata and allows to load resource
 */
class COPPER_API BundleDeserializer
{
public:
    enum Error : uint32_t
    {
        FailedToReadVersion = 1 << 0,
        FailedToReadMetatable = 1 << 1,
    };

public:
    explicit BundleDeserializer(const std::filesystem::path& bundlePath);

    /*!
     * \brief Deserialize:
     * loads meta data of bundle into memory.
     *
     * \returns if loading was successful
     */
    bool Deserialize();

    /*!
     * \brief GetResource:
     * loads resource from bundle into memory.
     * Can be used from multiple thread at the same time.
     * Doesn't have cache inside so multiple calls with the same param will end up in the same 2 resources in the memory
     *
     * \returns loaded resource or nullptr if given file doesn't exist
     */
    Ref<Resource> GetResource(const std::string& name) const;

    /*!
     * \brief GetErrorFlags:
     * \returns error flags filled during Deserialize execution
     */
    inline uint32_t GetErrorFlags() const { return m_ErrorFlags; }
    inline bool HasError() const { return m_ErrorFlags != 0; }

private:
    std::unordered_map<uint64_t, FileMeta> m_Metatable;
    uint32_t m_ErrorFlags{ 0 };
    uint32_t m_VersionMajor{ 0 };
    uint32_t m_VersionMinor{ 0 };
    std::filesystem::path m_BundlePath;
};

} // namespace Copper
