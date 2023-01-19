#pragma once

#include "IReadStream.h"

namespace Copper
{
/*!
 * \brief ReadStreamBase:
 * implements data processors handling logic for read stream
 */
class ReadStreamBase : public IReadStream
{
public:
    virtual uint64_t Read(char* buffer, uint64_t size) override;
    virtual void AddDataProcessor(const Copper::Ref<IDataProcessor>& dataProcessor) override;
    virtual void DeleteDataProcessor(const Ref<IDataProcessor>& dataProcessor) override;
    virtual bool HasError() const override;

    /*!
     * \brief ReadStreamBase::SetInternalBufferChunkSize:
     * sets chunk size buffer. Be wary, it doesn't mean that internal buffer will be \param size. It depends on amount
     * of data processors
     */
    inline void SetInternalBufferChunkSize(uint64_t size) { m_InternalBufferChunkSize = size; };

private:
    virtual uint64_t ReadChunk(char* buffer, uint64_t size) = 0;

    void InitInternalBuffer();
    std::vector<std::pair<char*, char*>> GetBuffersOrder();

private:
    std::vector<Ref<IDataProcessor>> m_DataProcessors;
    Scoped<char[]> m_InternalBuffer;
    uint64_t m_InternalBufferChunkSize{ 0 };
    uint64_t m_CurrentBufferSize{ 0 };
};
} // namespace Copper
