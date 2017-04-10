#include "field.hpp"


Field::Field(Type type, const std::string& name, uint16 flags):
    Variable(type, name),
    flags(flags)
{
}


std::string Field::str() const
{
    std::string str;

    if(flags & AccPublic)
        str += "public ";

    if(flags & AccPrivate)
        str += "private ";

    if(flags & AccProtected)
        str += "protected ";

    if(flags & AccStatic)
        str += "static ";

    if(flags & AccFinal)
        str += "final ";

    if(flags & AccVolatile)
        str += "volatile ";

    if(flags & AccTransient)
        str += "transient ";

    if(flags & AccSynthetic)
        str += "synthetic ";

    if(flags & AccEnum)
        str += "enum ";

    str += Variable::str();

    return str;
}
