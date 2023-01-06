#include "versionsection.h"

namespace Copper
{
void readVersionSection(std::ifstream& stream, BundleReadContext& context)
{
    stream.read((char*)&context.VersionMajor, sizeof(context.VersionMajor));
    stream.read((char*)&context.VersionMinor, sizeof(context.VersionMinor));
}

void writeVersionSection(std::ofstream& stream, BundleWriteContext& context)
{
    stream.write((char*)&context.VersionMajor, sizeof(context.VersionMajor));
    stream.write((char*)&context.VersionMinor, sizeof(context.VersionMinor));
}

} // namespace Copper
