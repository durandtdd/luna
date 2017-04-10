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

    case Void:
        s += "void";
        break;
    }

    for(uint32 k=0; k<dimensions; k++)
        s += "[]";

    return s;
}


bool operator==(const Type& type1, const Type& type2)
{
    return (type1.type == type2.type) &&
            (type1.object == type2.object) &&
            (type1.dimensions == type2.dimensions);
}


bool operator!=(const Type& type1, const Type& type2)
{
    return !(type1 == type2);
}
