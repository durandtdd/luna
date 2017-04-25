#include "type.hpp"


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


std::string Type::str() const
{
    std::string s;

    switch(type)
    {
        case Type::Object:  s += object; break;
        case Type::Boolean: s += "boolean"; break;
        case Type::Byte:    s += "byte"; break;
        case Type::Char:    s += "char"; break;
        case Type::Double:  s += "double"; break;
        case Type::Float:   s += "float"; break;
        case Type::Int:     s += "int"; break;
        case Type::Long:    s += "long"; break;
        case Type::Short:   s += "short"; break;
        case Type::Void:    s += "void"; break;
    }

    for(uint32 k=0; k<dimensions; k++)
        s += "[]";

    return s;
}
