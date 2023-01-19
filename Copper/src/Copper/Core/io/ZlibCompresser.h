#pragma once

#include "IDataProcessor.h"

#include <zlib.h>

namespace Copper
{
/*!
 * \brief ZlibCompresser:
 * data processor that deflates income data.
 */
class ZlibCompresser : public IDataProcessor
{
public:
    ZlibCompresser();
    ~ZlibCompresser();

    uint64_t Process(const char* fromBuffer, uint64_t fromSize, char* toBuffer, uint64_t toSize,
                     bool lastChunk) override;
    inline bool HasError() const override { return m_Error; }

private:
    void EndDeflate();

private:
    z_stream m_ZlibStream;
    bool m_IsEnded{ false };
    bool m_Error{ false };
};
} // namespace Copper
