#include "Resource.h"

namespace Copper
{
Resource::Resource(const std::string& name, uint64_t size = 0, const char* blob = nullptr,
                   FileMime::Type mime = FileMime::None)
    : m_Name(name), m_Size(size), m_Blob(blob), m_Mime(mime)
{
}

Resource::~Resource()
{
    if (m_Blob)
        delete m_Blob;
}
} // namespace Copper