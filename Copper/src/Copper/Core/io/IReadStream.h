#pragma once

#include "Copper/Core/Core.h"
#include "IDataProcessor.h"

namespace Copper
{
/*!
 * \brief IReadStream:
 * represents an interface for read stream with data processors
 */
class IReadStream
{
public:
    virtual ~IReadStream() = default;

    /*!
     * \brief IReadStream::Read:
     * reads \param size amount of data into \param buffer
     */
    virtual uint64_t Read(char* buffer, uint64_t size) = 0;

    /*!
     * \brief IReadStream::GetPos:
     * \returns current position in file
     */
    virtual uint64_t GetPos() = 0;

    /*!
     * \brief IReadStream::IsEof:
     * \returns whether file stream reached end of file
     */
    virtual bool IsEof() = 0;

    /*!
     * \brief IReadStream::HasError:
     * \returns is any error occured during reading. Be wary, unlike std::ifstream, it doesn't return true on EOF
     */
    virtual bool HasError() const = 0;

    /*!
     * \brief IReadStream::AddDataProcessor:
     * add data processor that is supposed to be executed on \ref Read method calling
     */
    virtual void AddDataProcessor(const Ref<IDataProcessor>& dataProcessor) = 0;

    /*!
     * \brief IReadStream::DeleteDataProcessor:
     * delete previously added processor. If there's no any, does nothing
     */
    virtual void DeleteDataProcessor(const Ref<IDataProcessor>& dataProcessor) = 0;
};
}
