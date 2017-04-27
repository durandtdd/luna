#pragma once

#include <type_traits>
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
 * @param first Iterator on first char to parse, is set to after last parsed char
 * @param last Last char of the descriptor
 * @return Parsed type
 */
template<typename InputIt>
Type parseDescriptor(InputIt&& first, typename std::remove_reference<InputIt>::type last)
{
    Type type;

    // Number of '[' at the beginning
    while(first != last && *first == '[')
    {
        type.dimensions++;
        first++;
    }

    // There must be at least one char after '[' sequence
    if(first == last)
        throw DescriptorParseError("Invalid descriptor");


    switch(*first)
    {
        case 'B':
            type.type = Type::Byte;
            break;

        case 'C':
            type.type = Type::Char;
            break;

        case 'D':
            type.type = Type::Double;
            break;

        case 'F':
            type.type = Type::Float;
            break;

        case 'I':
            type.type = Type::Int;
            break;

        case 'J':
            type.type = Type::Long;
            break;

        case 'S':
            type.type = Type::Short;
            break;

        case 'V':
            type.type = Type::Void;
            break;

        case 'Z':
            type.type = Type::Boolean;
            break;

        case 'L':
            type.type = Type::Object;
            type.object = "";
            while(true)
            {
                if(++first == last)
                    throw DescriptorParseError("Invalid descriptor");

                if(*first == ';')
                    break;

                type.object += *first;
            }
            std::replace(type.object.begin(), type.object.end(), '/', '.');
            break;

        default:
            throw DescriptorParseError("Invalid descriptor");
    }

    first++;

    return type;
}


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
 * @param first Iterator on first char to parse, is set to after last parsed char
 * @param last Last char of the descriptor
 * @return Parsed method descriptor
 */
template<typename InputIt>
ParsedMethodDescriptor parseMethodDescriptor(InputIt&& first, typename std::remove_reference<InputIt>::type last)
{
    ParsedMethodDescriptor parsed;

    if(*first != '(')
        throw DescriptorParseError("Invalid descriptor");

    ++first; // '('
    while(*first != ')')
    {
        Type type = parseDescriptor(std::forward<InputIt>(first), last);
        Variable var {type, "param" + std::to_string(parsed.parameters.size())};
        parsed.parameters.push_back(var);
    }

    ++first; // ')'

    parsed.type = parseDescriptor(std::forward<InputIt>(first), last);

    return parsed;
}


