#include "assetssection.h"
#include "Copper/Core/Log.h"

namespace Copper
{
void writeAssetsSection(std::ofstream& stream, BundleWriteContext& context, const std::filesystem::path& dir)
{
    static constexpr uint32_t maxSizeToRead = 1024 * 1024 * 40;
    char* dataBuffer = (char*)std::malloc(maxSizeToRead);

    for (int i = 0; i < context.ParsedFilesData.size(); ++i)
    {
        const std::filesystem::path filePath = dir.string() + '/' + context.ParsedFilesData[i].Path;

        CPR_CORE_INFO("Writing file {0}", filePath.string());

        std::ifstream bundleFileStream(filePath, std::ios::binary | std::ios::in);

        while (bundleFileStream.peek() != EOF)
        {
            bundleFileStream.read(dataBuffer, maxSizeToRead);

            const uint32_t dataSizeRead = bundleFileStream.gcount();
            stream.write(dataBuffer, dataSizeRead);
        }

        CPR_CORE_INFO("Done");
    }
}
} // namespace Copper
