#pragma once

#include <string>
#include <vector>

#include "../common.hpp"
#include "../java-objects/type.hpp"
#include "../java-objects/variable.hpp"


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


/**
 * @brief Structure returned by the parseMethodDescriptor
 */
struct ParsedMethodDescriptor
{
    /** Return type */
    Type type;

    /** Param types */
    std::vector<Variable> parameters;
};


/**
 * @brief Parse a method descriptor
 * @param first Iterator on first char to parse, is set to after last char parsed
 * @param last Last char of the descriptor
 * @return Parsed method descriptor
 */
ParsedMethodDescriptor parseMethodDescriptor(std::string::iterator& first, std::string::iterator last);
