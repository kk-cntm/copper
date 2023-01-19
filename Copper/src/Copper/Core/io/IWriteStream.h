#pragma once

#include "Copper/Core/Core.h"
#include "IDataProcessor.h"

namespace Copper
{
class IWriteStream
{
public:
    virtual ~IWriteStream() = default;

    /*!
     * \brief IWriteStream::Write:
     * writes \param size amount of data into \param buffer.
     *
     * \param lastChunk - indicates if this chunk is the last one
     */
    virtual uint64_t Write(const char* buffer, uint64_t size, bool lastChunk) = 0;

    /*!
     * \brief IWriteStream::GetPos:
     * \returns current position in file
     */
    virtual uint64_t GetPos() = 0;

    /*!
     * \brief IWriteStream::SeekPos:
     * moves current file position to \param pos from beginning
     */
    virtual void SeekPos(uint64_t pos) = 0;

    /*!
     * \brief IWriteStream::IsEof:
     * \returns whether file stream reached end of file
     */
    virtual bool IsEof() = 0;

    /*!
     * \brief IWriteStream::HasError:
     * \returns is any error occured during reading. Be wary, unlike std::ofstream, it doesn't return true on EOF
     */
    virtual bool HasError() const = 0;

    /*!
     * \brief IWriteStream::AddDataProcessor:
     * add data processor that is supposed to be executed on \ref Write method calling
     */
    virtual void AddDataProcessor(const Ref<IDataProcessor>& dataProcessor) = 0;

    /*!
     * \brief IWriteStream::DeleteDataProcessor:
     * delete previously added processor. If there's no any, does nothing
     */
    virtual void DeleteDataProcessor(const Ref<IDataProcessor>& dataProcessor) = 0;
};
}
