#include "ReadStreamBase.h"

namespace Copper
{

uint64_t ReadStreamBase::Read(char *buffer, uint64_t size)
{
    const uint64_t prevPos = GetPos();

    uint64_t bytesProcessed = size;

    if (!m_DataProcessors.empty())
    {
        InitInternalBuffer();
        const auto buffersOrder = GetBuffersOrder();

        char* lastBuffer = std::get<0>(buffersOrder.at(0));
        bytesProcessed = ReadChunk(lastBuffer, size);

        for (int i = 0; i < m_DataProcessors.size() - 1; ++i)
        {
            auto& dataProcessor = m_DataProcessors[i];
            auto& [bufferFrom, bufferTo] = buffersOrder.at(i % buffersOrder.size());

            bytesProcessed = dataProcessor->Process(bufferFrom, bytesProcessed, bufferTo, m_InternalBufferChunkSize,
                                                    IsEof());

            lastBuffer = bufferTo;
            if (dataProcessor->HasError())
                return 0;
        }
        {
            auto& dataProcessor = m_DataProcessors[m_DataProcessors.size() - 1];

            bytesProcessed = dataProcessor->Process(lastBuffer, bytesProcessed, buffer, size,
                                                    IsEof());
            if (dataProcessor->HasError())
                return 0;
        }
    }
    else
    {
        bytesProcessed = ReadChunk(buffer, bytesProcessed);
    }

    return bytesProcessed;

}

void ReadStreamBase::AddDataProcessor(const Copper::Ref<IDataProcessor>& dataProcessor)
{
    m_DataProcessors.emplace_back(dataProcessor);
}

void ReadStreamBase::DeleteDataProcessor(const Ref<IDataProcessor> &dataProcessor)
{
    m_DataProcessors.erase(std::remove_if(m_DataProcessors.begin(), m_DataProcessors.end(),
                                          [&dataProcessor](auto& currentProcessor)
                                          { return currentProcessor.get() == dataProcessor.get(); }),
                           m_DataProcessors.end());
}

bool ReadStreamBase::HasError() const
{
    return std::any_of(m_DataProcessors.cbegin(), m_DataProcessors.cend(),
                       [](auto& dataProcessor) { return dataProcessor->HasError(); });
}

void ReadStreamBase::InitInternalBuffer()
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

std::vector<std::pair<char*, char*>> ReadStreamBase::GetBuffersOrder()
{
    char* buffer1 = m_InternalBuffer.get();
    char* buffer2 = buffer1 + m_InternalBufferChunkSize;
    char* buffer3 = buffer2 + m_InternalBufferChunkSize;

    return { { buffer1, buffer2 }, { buffer2, buffer3 }, { buffer3, buffer1 } };
}
}
