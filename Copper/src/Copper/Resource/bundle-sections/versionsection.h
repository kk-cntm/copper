#pragma once

#include "Copper/Resource/context.h"

namespace Copper
{
/*!
 * \brief readVersionSection:
 * reads version from bundle file
 */
void readVersionSection(std::ifstream& stream, BundleReadContext& context);

/*!
 * \brief writeVersionSection:
 * writes version into bundle file
 */
void writeVersionSection(std::ofstream& stream, BundleWriteContext& context);
} // namespace Copper
