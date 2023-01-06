#pragma once

#include "Copper/Resource/context.h"

namespace Copper
{
/*!
 * \brief writeAssetsSection:
 * writes down listed in \param context assets into bundle file.
 */
void writeAssetsSection(std::ofstream& stream, BundleWriteContext& context, const std::filesystem::path& dir);
} // namespace Copper
