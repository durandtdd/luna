#include "descriptor-parser.hpp"

#include <algorithm>


Type parseDescriptor(std::string::iterator& first, std::string::iterator last)
{
    Type type;

    // Number of '[' at the beginning
    while(first < last && *first == '[')
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


ParsedMethodDescriptor parseMethodDescriptor(std::string::iterator& first, std::string::iterator last)
{
    ParsedMethodDescriptor parsed;

    if(*first != '(')
        throw DescriptorParseError("Invalid descriptor");

    ++first; // '('
    while(*first != ')')
    {
        Type type = parseDescriptor(first, last);
        Variable var {type, "param" + std::to_string(parsed.parameters.size())};
        parsed.parameters.push_back(var);
    }

    ++first; // ')'

    parsed.type = parseDescriptor(first, last);

    return parsed;
}
