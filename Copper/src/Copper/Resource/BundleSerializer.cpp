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
    if (!ParseConfigFile())
        return false;

    if (!PackFiles())
        std::filesystem::remove(m_OutputPath);

    return true;
}

bool BundleSerializer::ParseConfigFile()
{
    uint32_t errors = 0;

    pugi::xml_document doc;
    const pugi::xml_parse_result parseResult = doc.load_file(m_ConfigPath.c_str());

    if (!parseResult)
    {
        CPR_CORE_ERROR("Failed to parse {} bundle: {}", m_ConfigPath, parseResult.description());
        m_ErrorFlags |= FailedToParseFileFormat;
        return false;
    }

    const auto root = doc.child("bundle");

    std::vector<ParsedFileData> result;

    for (const pugi::xml_node& fileNode : root.children("file"))
    {
        ParsedFileData file;
        file.Path = fileNode.attribute("path").as_string();

        if (file.Path.empty())
        {
            CPR_CORE_ERROR("Failed to parse file path in bundle {}", m_ConfigPath);
            m_ErrorFlags |= FailedToParseConfig;
            return false;
        }

        file.Mime = FileMime::FromMimeString(fileNode.attribute("mime").as_string());

        if (file.Mime == FileMime::None)
        {
            CPR_CORE_ERROR("Failed to parse mime type for {}", file.Path);
            m_ErrorFlags |= FailedToParseConfig;
            return false;
        }

        result.push_back(std::move(file));
    }

    m_ParsedFiles = std::move(result);

    return true;
}

bool BundleSerializer::PackFiles()
{
    const auto configFileDir = m_ConfigPath.parent_path();
    std::ofstream stream(m_OutputPath, std::ofstream::binary);

    VersionSectionWriter versionWriter(stream);
    if (!versionWriter.Write(VERSION_MAJOR, VERSION_MINOR))
    {
        m_ErrorFlags |= FailedToWriteVersion;
        return false;
    }

    const uint64_t metatablePos = stream.tellp();
    const uint64_t metatableSize = MetaTableSectionWriter::CalculateMetadataSize(m_ParsedFiles);

    stream.seekp(metatablePos + metatableSize, std::ifstream::beg);

    AssetsSectionWriter assetsWriter(stream, configFileDir);
    if (!assetsWriter.Write(m_ParsedFiles))
    {
        m_ErrorFlags |= FailedToWriteAssets;
        return false;
    }

    const auto filesLayout = assetsWriter.GetFilesLayout();

    stream.seekp(metatablePos, std::ifstream::beg);

    MetaTableSectionWriter metatableWriter(stream, configFileDir);
    if (!metatableWriter.Write(m_ParsedFiles, filesLayout))
    {
        m_ErrorFlags |= FailedToWriteMetatable;
        return false;
    }

    return true;
}

} // namespace Copper
