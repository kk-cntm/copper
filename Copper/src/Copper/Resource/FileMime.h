#pragma once

#include "cprpch.h"

namespace Copper::FileMime
{
enum Type : uint16_t
{
    None,
    Bmp
};

/*!
 * \brief FileMime::ToMimeString:
 * transforms given mime type to corresponding string representation
 * 
 * \param type - mime type to be transformed
 */
std::string ToMimeString(Type type);

/*!
 * \brief FileMime::FromMimeString:
 * transforms given mime type string representation into enum value
 * 
 * \param mime - mime type string
 */
Type FromMimeString(const ::std::string& mime);

}