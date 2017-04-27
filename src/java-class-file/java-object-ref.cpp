#include "java-object-ref.hpp"

#include "../utils.hpp"


FieldRef::FieldRef()
{
    refType = Field;
}


std::string FieldRef::str() const
{
    return type.str() + " " + className + "." + name;
}


MethodRef::MethodRef()
{
    refType = Method;
}


std::string MethodRef::str() const
{
    std::string s = type.str() + " " + className + "." + name;
    s += "(";
    s += strjoin(parameters.begin(), parameters.end(), ", ", [](const auto& e){return e.str();});
    s += ")";
    return s;
}


ClassRef::ClassRef()
{
    refType = Class;
}


std::string ClassRef::str() const
{
    return className;
}
