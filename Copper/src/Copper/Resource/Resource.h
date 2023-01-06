#pragma once

#include "FileMime.h"
#include "Copper/Core/Core.h"

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
     * \brief Resource:
     * \param name - resource name
     * \param size - resource size
     * \param blob - resource blob. MUST BE IN HEAP
     * \param mome - resouce mime type (e.g image/bmp)
     */
    explicit Resource(const std::string& name, uint64_t size, const char* blob, FileMime::Type mime);
    ~Resource();

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
     * \brief Resource::GetBlob:
     * \returns actual data blob of the asset
     */
    inline const char* GetBlob() const { return m_Blob; }

    /*!
     * \brief Resource::GetMime:
     * \returns actual mime type of the asset
     */
    inline FileMime::Type GetMime() const { return m_Mime; }

private:
    std::string m_Name;
    const uint64_t m_Size;
    const char* m_Blob;
    const FileMime::Type m_Mime;
};

} // namespace Copper
