#include "Resource.h"

namespace Copper
{
Resource::Resource(const Params& params)
    : m_Name(params.Name),
      m_Size(params.Size),
      m_CompressedSize(params.CompressedSize),
      m_BundlePath(params.BundlePath),
      m_Offset(params.Offset),
      m_Mime(params.Mime)
{
}

} // namespace Copper
