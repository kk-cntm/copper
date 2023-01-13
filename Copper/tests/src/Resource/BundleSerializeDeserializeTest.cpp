#include "fixtures/BaseApplicationTest.h"

#include "Copper/Resource/BundleDeserializer.h"
#include "Copper/Resource/BundleSerializer.h"

#include <gtest/gtest.h>
#include <iosfwd>

namespace
{
const std::filesystem::path CACHE_DIR = ".testscache";
const std::filesystem::path RESOURCES_DIR = "resources";
const std::filesystem::path BUNDLE_PATH = CACHE_DIR / "testbundle.bundle";
const std::filesystem::path CONFIG_XML_PATH = RESOURCES_DIR / "testbundle.xml";
} // namespace

class BundleSerializeDeserializeTest : public BaseApplicationTest, public ::testing::WithParamInterface<std::string>
{
protected:
    void SetUp() override
    {
        std::filesystem::create_directory(CACHE_DIR);

        auto serializer = Copper::MakeRef<Copper::BundleSerializer>(CONFIG_XML_PATH, BUNDLE_PATH);
        serializer->Serialize();

        ASSERT_FALSE(serializer->HasError());

        m_Deserializer = Copper::MakeRef<Copper::BundleDeserializer>(BUNDLE_PATH);
        m_Deserializer->Deserialize();

        ASSERT_FALSE(m_Deserializer->HasError());
    }

    void TearDown() override { std::filesystem::remove(BUNDLE_PATH); }

    static std::filesystem::path GetResourcePath(const std::string& name) { return RESOURCES_DIR / name; }

    ::testing::AssertionResult compareBlobs(std::ifstream& stream, Copper::ResourceReader& reader, uint64_t size)
    {
        auto readerBuffer = Copper::MakeScoped<char[]>(reader.GetChunkSize());
        auto streamBuffer = Copper::MakeScoped<char[]>(reader.GetChunkSize());

        uint64_t totalBytesRead = 0;
        while (!reader.IsEof())
        {
            const uint64_t bytesCount = reader.ReadChunk(readerBuffer);

            if (bytesCount == 0)
                return ::testing::AssertionFailure() << "Expected bytesCount to be greater than 0";

            if (reader.HasError())
                return ::testing::AssertionFailure() << "Could not read a chunk";

            stream.read(streamBuffer.get(), bytesCount);
            if (stream.fail() || stream.bad())
                return ::testing::AssertionFailure() << std::strerror(errno);

            for (int i = 0; i < bytesCount; ++i)
            {
                if (*(streamBuffer.get() + i) != *(readerBuffer.get() + i))
                    return ::testing::AssertionFailure() << "at " << i << " byte";
            }

            totalBytesRead += bytesCount;
        }

        return ::testing::AssertionSuccess();
    }

protected:
    Copper::Ref<Copper::BundleDeserializer> m_Deserializer;
};

TEST_P(BundleSerializeDeserializeTest, shouldSerializeAndDeserializeFileWithoutMangling)
{
    const auto resource = m_Deserializer->GetResource(GetParam());
    ASSERT_TRUE(resource);

    const auto originalFilePath = GetResourcePath(GetParam());
    const auto originalFileSize = std::filesystem::file_size(originalFilePath);

    ASSERT_EQ(originalFileSize, resource->GetSize());

    std::ifstream originalFileStream(originalFilePath, std::ifstream::binary);
    auto reader = resource->CreateReader();

    ASSERT_TRUE(compareBlobs(originalFileStream, reader, originalFileSize));
}

// here goes all expected files from bundle
const auto files = ::testing::Values("testbitmap.bmp");
INSTANTIATE_TEST_SUITE_P(BundleSerializeDeserializeParamTest, BundleSerializeDeserializeTest, files);
