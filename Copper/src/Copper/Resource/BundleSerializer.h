#pragma once

#include "context.h"
#include "Copper/Core/Core.h"

namespace Copper
{
/*!
 * \brief BundleSerializer:
 * implements logic for serialization of a bunch of assets specified in a "bundle config file"
 */
class COPPER_API BundleSerializer
{
public:
    enum Error : uint32_t
    {
        FailedToParseFileFormat = 1 << 0,
        FailedToParseConfig = 1 << 1
    };

public:
    explicit BundleSerializer(const std::filesystem::path& configPath, const std::filesystem::path& outputPath);

    /*!
     * \brief BundleSerializer:
     * creates asset bundle from given config file
     * 
     * \returns if serialization was successful
     */
    bool Serialize();

    inline uint32_t GetErrorFlags() const { return m_ErrorFlags; }
    inline bool HasError() const { return m_ErrorFlags != 0; }

private:
    void ParseConfigFile();
    void PackFiles();

private:
    uint32_t m_ErrorFlags{ 0 };
    std::filesystem::path m_ConfigPath;
    std::filesystem::path m_OutputPath;
    std::vector<ParsedFileData> m_ParsedFiles;

    static constexpr int VERSION_MAJOR = 0;
    static constexpr int VERSION_MINOR = 1;
};

} // namespace Copper
