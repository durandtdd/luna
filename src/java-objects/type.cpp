#include "type.hpp"


Type::Type(Type::Enum type, const std::string& object, uint32 dimensions):
    type(type),
    object(object),
    dimensions(dimensions)
{
}


std::string Type::str() const
{
    std::string s = "";

    switch(type)
    {
    case Object:
        s += object;
        break;

    case Boolean:
        s += "boolean";
        break;

    case Byte:
        s += "byte";
        break;

    case Char:
        s += "char";
        break;

    case Double:
        s += "double";
        break;

    case Float:
        s += "float";
        break;

    case Int:
        s += "int";
        break;

    case Long:
        s += "long";
        break;

    case Short:
        s += "short";
        break;

    }

    for(uint32 k=0; k<dimensions; k++)
        s += "[]";

    return s;
}
