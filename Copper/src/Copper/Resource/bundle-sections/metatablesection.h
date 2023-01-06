#pragma once

#include "Copper/Resource/context.h"

namespace Copper
{
/*!
 * \brief readMetaTableSection:
 * reads metatable from bundle file into \param context
 */
void readMetaTableSection(std::ifstream& stream, BundleReadContext& context);

/*!
 * \brief writeMetaTableSection:
 * writes metatable to bundle file from \param context
 */
void writeMetaTableSection(std::ofstream& stream, BundleWriteContext& context, const std::filesystem::path& dir);
} // namespace Copper
