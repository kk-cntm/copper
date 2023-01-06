#include "BundleSerializer.h"
#include "bundle-sections/versionsection.h"
#include "bundle-sections/metatablesection.h"
#include "bundle-sections/assetssection.h"
#include "Copper/Core/Log.h"

#include <pugixml.hpp>

namespace Copper
{

BundleSerializer::BundleSerializer(const std::filesystem::path& configPath, const std::filesystem::path& outputPath)
    : m_ConfigPath(configPath), m_OutputPath(outputPath)
{
}

bool BundleSerializer::Serialize()
{
    ParseConfigFile();
    if (HasError())
        return false;

    PackFiles();
    if (HasError())
        return false;

    return true;
}

void BundleSerializer::ParseConfigFile()
{
    uint32_t errors = 0;

    pugi::xml_document doc;
    const pugi::xml_parse_result parseResult = doc.load_file(m_ConfigPath.c_str());

    if (!parseResult)
    {
        CPR_CORE_ERROR("Failed to parse {} bundle: {}", m_ConfigPath, parseResult.description());
        m_ErrorFlags |= FailedToParseFileFormat;
        return;
    }

    const auto root = doc.child("bundle");

    std::vector<ParsedFileData> result;
    result.reserve(std::distance(root.begin(), root.end()));

    for (const pugi::xml_node& fileNode : root.children("file"))
    {
        ParsedFileData file;
        file.Path = fileNode.attribute("path").as_string();

        if (file.Path.empty())
        {
            CPR_CORE_ERROR("Failed to parse file path in bundle {}", m_ConfigPath);
            m_ErrorFlags |= FailedToParseConfig;
            return;
        }

        file.Mime = FileMime::FromMimeString(fileNode.attribute("mime").as_string());

        if (file.Mime == FileMime::None)
        {
            CPR_CORE_ERROR("Failed to parse mime type for {}", file.Path);
            m_ErrorFlags |= FailedToParseConfig;
            return;
        }

        result.push_back(std::move(file));
    }

    m_ParsedFiles = std::move(result);
}

void BundleSerializer::PackFiles()
{
    BundleWriteContext context;
    context.VersionMajor = VERSION_MAJOR;
    context.VersionMajor = VERSION_MINOR;
    context.ParsedFilesData = m_ParsedFiles;

    const auto configFileDir = m_ConfigPath.parent_path();
    std::ofstream stream(m_OutputPath, std::ofstream::binary);

    writeVersionSection(stream, context);
    writeMetaTableSection(stream, context, configFileDir);
    writeAssetsSection(stream, context, configFileDir);
}

} // namespace Copper
