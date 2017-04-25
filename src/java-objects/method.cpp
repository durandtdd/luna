#include "method.hpp"

#include "../utils.hpp"


std::string Method::str(bool allFlags) const
{
    std::string s;

    // Flags
    if(flags & Method::AccPublic)
        s += "public ";

    if(flags & Method::AccPrivate)
        s += "private ";

    if(flags & Method::AccProtected)
        s += "protected ";

    if(flags & Method::AccStatic)
        s += "static ";

    if(flags & Method::AccFinal)
        s += "final ";

    if(flags & Method::AccSynchronized)
        s += "synchronized ";

    if(flags & Method::AccBridge)
        s += "bridge ";

    if(allFlags && (flags & Method::AccVarArgs))
        s += "varargs ";

    if(flags & Method::AccNative)
        s += "native ";

    if(flags & Method::AccAbstract)
        s += "abstract ";

    if(allFlags && (flags & Method::AccStrict))
        s += "strict ";

    if(allFlags && (flags & Method::AccSynthetic))
        s += "synthetic ";

    // Type and name
    s += type.str();
    s += " ";
    s += name;

    // Parameters
    s += "(";
    s += strjoin(parameters.begin(), parameters.end(), ", ", [](const auto& p) {return p.str();});
    s += ")";

    return s;
}
