#pragma once

#include "FileMime.h"
#include "Copper/Core/Core.h"
#include "ResourceReader.h"

namespace Copper
{
/*!
 * \brief Resource:
 * represents arbitary asset
 */
class COPPER_API Resource
{
public:
    /*!
     * \brief Resource::Params:
     * \param Name - resource name
     * \param Size - resource size
     * \param BundlePath - path to the bundle path the resouce belong to
     * \param Offset - resource offset in bundle file in bytes
     * \param Mime - resouce mime type (e.g image/bmp)
     */
    struct Params
    {
        std::string Name;
        std::filesystem::path BundlePath;
        uint64_t Size;
        uint64_t CompressedSize;
        uint64_t Offset;
        FileMime::Type Mime;
    };

public:
    Resource();
    explicit Resource(const Params& params);

    /*!
     * \brief Resource::GetName
     * \returns the name of the resource
     */
    inline const std::string& GetName() const { return m_Name; }

    /*!
     * \brief Resource::GetSize:
     * \returns actual size of the asset
     */
    inline uint64_t GetSize() const { return m_Size; }

    /*!
     * \brief Resource::GetMime:
     * \returns actual mime type of the asset
     */
    inline FileMime::Type GetMime() const { return m_Mime; }

    /*!
     * \brief Resource::CreateReader:
     * \returns creates chunk reader for current resource
     */
    inline ResourceReader CreateReader() const
    {
        return ResourceReader(m_BundlePath, m_CompressedSize, m_Offset);
    };

private:
    std::string m_Name;
    std::filesystem::path m_BundlePath;
    uint64_t m_Offset;
    uint64_t m_Size;
    uint64_t m_CompressedSize;
    FileMime::Type m_Mime;
};

} // namespace Copper
