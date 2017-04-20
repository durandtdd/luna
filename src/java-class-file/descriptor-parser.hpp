#pragma once

#include <string>

#include "../common.hpp"
#include "../java-objects/type.hpp"


/**
 * @brief Error thrown if descriptor can't be parsed
 */
class DescriptorParseError: public Error
{
public:
    using Error::Error;
};


/**
 * @brief Parse a descriptor
 * @param first Iterator on first char to parse, is set to after last char parsed
 * @param last Last char of the descriptor
 * @return Parsed type
 */
Type parseDescriptor(std::string::iterator& first, std::string::iterator last);
