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

        m_Serializer = Copper::MakeRef<Copper::BundleSerializer>(CONFIG_XML_PATH, BUNDLE_PATH);
        m_Serializer->Serialize();

        ASSERT_FALSE(m_Serializer->HasError());

        m_Deserializer = Copper::MakeRef<Copper::BundleDeserializer>(BUNDLE_PATH);
        m_Deserializer->Deserialize();

        ASSERT_FALSE(m_Deserializer->HasError());
    }

    void TearDown() override { std::filesystem::remove(BUNDLE_PATH); }

    static std::filesystem::path GetResourcePath(const std::string& name) { return RESOURCES_DIR / name; }

protected:
    Copper::Ref<Copper::BundleSerializer> m_Serializer;
    Copper::Ref<Copper::BundleDeserializer> m_Deserializer;
};

::testing::AssertionResult compareBlobs(const char* blob1, const char* blob2, uint64_t size)
{
    for (int i = 0; i < size; ++i)
    {
        if (*(blob1 + i) != *(blob2 + i))
            return ::testing::AssertionFailure() << "at " << i << " byte";
    }

    return ::testing::AssertionSuccess();
}

TEST_P(BundleSerializeDeserializeTest, shouldSerializeAndDeserializeFileWithoutMangling)
{
    const auto resource = m_Deserializer->GetResource(GetParam());
    ASSERT_TRUE(resource);

    const auto originalFilePath = GetResourcePath(GetParam());
    const auto originalFileSize = std::filesystem::file_size(originalFilePath);

    ASSERT_EQ(originalFileSize, resource->GetSize());

    std::ifstream originalFileStream(originalFilePath, std::ifstream::binary);
    char* originalBlob = (char*)std::malloc(originalFileSize);
    originalFileStream.read(originalBlob, originalFileSize);

    ASSERT_TRUE(compareBlobs(originalBlob, resource->GetBlob(), originalFileSize));
}

// here goes all expected files from bundle
const auto files = ::testing::Values("testbitmap.bmp");
INSTANTIATE_TEST_SUITE_P(BundleSerializeDeserializeParamTest, BundleSerializeDeserializeTest, files);
