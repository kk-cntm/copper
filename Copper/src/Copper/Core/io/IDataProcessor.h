#pragma once

#include <unistd.h>

namespace Copper
{
/*!
 * \brief IDataProcessor:
 * represents an interface for data processors used in streams.
 * It might be different coders/decoders.
 * For instance: ZlibCompressor
 */
class IDataProcessor
{
public:
    virtual ~IDataProcessor() = default;

    /*!
     * \brief IDataProcessor::Process:
     * process given chunk of data.
     *
     * \param fromBuffer - original data
     * \param fromSize - size of original data
     * \param toBuffer - buffer where to write (must be at least \param toSize size)
     * \param toSize - size of \param toBuffer
     * \param lastChunk - is current chunk last. Used for finishing up the job
     */
    virtual uint64_t Process(const char* fromBuffer, uint64_t fromSize, char* toBuffer, uint64_t toSize, bool lastChunk)
        = 0;

    /*!
     * \brief IDataProcessor::HasError:
     * \returns whether any error occured during processing
     */
    virtual bool HasError() const = 0;
};
} // namespace Copper
