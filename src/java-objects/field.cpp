#include "field.hpp"


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

    str += type.str() + " " + name;

    return str;
}


bool operator==(const Field& field1, const Field& field2)
{
    return (field1.type == field2.type) &&
            (field1.name == field2.name) &&
            (field1.flags == field2.flags);
}


bool operator!=(const Field& field1, const Field& field2)
{
    return !(field1 == field2);
}
