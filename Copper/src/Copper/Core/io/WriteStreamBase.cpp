#include "WriteStreamBase.h"

namespace Copper
{
uint64_t WriteStreamBase::Write(const char* buffer, uint64_t size, bool lastChunk)
{
    const uint64_t prevPos = GetPos();

    uint64_t bytesProcessed = size;

    if (!m_DataProcessors.empty())
    {
        InitInternalBuffer();

        const auto buffersOrder = GetBuffersOrder();
        char* bufferToWrite;

        {
            auto& dataProcessor = m_DataProcessors[0];
            auto& [bufferTo, _] = buffersOrder.at(0);

            bytesProcessed = dataProcessor->Process(buffer, bytesProcessed, bufferTo, m_InternalBufferChunkSize,
                                                    lastChunk);

            bufferToWrite = bufferTo;
            if (dataProcessor->HasError())
                return 0;
        }

        for (int i = 1; i < m_DataProcessors.size(); ++i)
        {
            auto& dataProcessor = m_DataProcessors[i - 1];
            auto& [bufferFrom, bufferTo] = buffersOrder.at(i % buffersOrder.size());

            bytesProcessed = dataProcessor->Process(bufferFrom, bytesProcessed, bufferTo, m_InternalBufferChunkSize,
                                                    lastChunk);

            bufferToWrite = bufferTo;

            if (dataProcessor->HasError())
                return 0;
        }

        WriteChunk(bufferToWrite, bytesProcessed);
    }
    else
    {
        WriteChunk(buffer, bytesProcessed);
    }

    return GetPos() - prevPos;
}

void WriteStreamBase::AddDataProcessor(const Ref<IDataProcessor>& dataProcessor)
{
    m_DataProcessors.emplace_back(dataProcessor);
}

void WriteStreamBase::DeleteDataProcessor(const Ref<IDataProcessor>& dataProcessor)
{
    m_DataProcessors.erase(std::remove_if(m_DataProcessors.begin(), m_DataProcessors.end(),
                                          [&dataProcessor](auto& existingDataProcessor)
                                          { return existingDataProcessor.get() == dataProcessor.get(); }),
                           m_DataProcessors.end());
}

bool WriteStreamBase::HasError() const
{
    return std::any_of(m_DataProcessors.cbegin(), m_DataProcessors.cend(),
                       [](auto& dataProcessor) { return dataProcessor->HasError(); });
}

void WriteStreamBase::InitInternalBuffer()
{
    if (m_DataProcessors.empty())
        return;

    uint64_t neededBufferSize;
    if (m_DataProcessors.size() > 2)
        neededBufferSize = m_InternalBufferChunkSize * 3;
    else if (m_DataProcessors.size() > 1)
        neededBufferSize = m_InternalBufferChunkSize * 2;
    else if (m_DataProcessors.size() > 0)
        neededBufferSize = m_InternalBufferChunkSize;

    if (m_CurrentBufferSize < neededBufferSize)
    {
        m_InternalBuffer.reset();
        m_InternalBuffer = MakeScoped<char[]>(neededBufferSize);
    }
    else if (!m_InternalBuffer)
    {
        m_InternalBuffer = MakeScoped<char[]>(neededBufferSize);
    }
}

std::vector<std::pair<char*, char*>> WriteStreamBase::GetBuffersOrder() const
{
    char* buffer1 = m_InternalBuffer.get();
    char* buffer2 = buffer1 + m_InternalBufferChunkSize;
    char* buffer3 = buffer2 + m_InternalBufferChunkSize;

    return { { buffer1, buffer2 }, { buffer2, buffer3 }, { buffer3, buffer1 } };
}
} // namespace Copper
