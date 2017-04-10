#include "method.hpp"

#include <algorithm>


Method::Method(const std::string& name, Type type, uint16 flags):
    name(name),
    type(type),
    flags(flags)
{
}


std::string Method::str() const
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

    if(flags & AccSynchronized)
        str += "synchronized ";

    if(flags & AccBridge)
        str += "bridge ";

    if(flags & AccVarArgs)
        str += "varargs ";

    if(flags & AccNative)
        str += "native ";

    if(flags & AccAbstract)
        str += "abstract ";

    if(flags & AccStrict)
        str += "strict ";

    if(flags & AccSynthetic)
        str += "synthetic ";

    str += type.str();
    str += " ";
    str += name;

    str += "(";
    for(std::size_t k=0; k<parameters.size(); k++)
    {
        str += parameters[k].str();
        if(k<parameters.size()-1)
            str += ", ";
    }
    str += ")";

    return str;
}


bool operator==(const Method& method1, const Method& method2)
{
    return (method1.type == method2.type) &&
            (method1.name == method2.name) &&
            (method1.flags == method2.flags) &&
            (method1.parameters.size() == method2.parameters.size()) &&
            std::equal(method1.parameters.begin(), method1.parameters.end(), method2.parameters.begin());
}


bool operator!=(const Method& method1, const Method& method2)
{
    return !(method1 == method2);
}
