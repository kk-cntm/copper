#pragma once

#include "IWriteStream.h"

namespace Copper
{
/*!
 * \brief WriteStreamBase:
 * implements data processors handling logic for write stream
 */
class WriteStreamBase : public IWriteStream
{
public:
    virtual uint64_t Write(const char* buffer, uint64_t size, bool lastChunk) override;
    virtual void AddDataProcessor(const Ref<IDataProcessor>& dataProcessor) override;
    virtual void DeleteDataProcessor(const Ref<IDataProcessor>& dataProcessor) override;
    virtual bool HasError() const override;

    /*!
     * \brief WriteStreamBase::SetInternalBufferChunkSize:
     * sets chunk size buffer. Be wary, it doesn't mean that internal buffer will be \param size. It depends on amount
     * of data processors
     */
    inline void SetInternalBufferChunkSize(uint64_t size) { m_InternalBufferChunkSize = size; }

private:
    virtual uint64_t WriteChunk(const char* buffer, uint64_t size) = 0;

    void InitInternalBuffer();
    std::vector<std::pair<char*, char*>> GetBuffersOrder() const;

private:
    std::vector<Ref<IDataProcessor>> m_DataProcessors;
    Scoped<char[]> m_InternalBuffer;
    uint64_t m_InternalBufferChunkSize{ 1024 * 16 };
    uint64_t m_CurrentBufferSize{ 0 };
};
} // namespace Copper
