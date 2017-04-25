#include "class.hpp"

#include "../utils.hpp"


std::string Class::str(bool allFlags) const
{
    std::string s;

    // Flags
    if(flags & Class::AccEnum)
        s += "enum ";

    if(flags & Class::AccPublic)
        s += "public ";

    if(flags & Class::AccAbstract)
        s += "abstract ";

    if(flags & Class::AccFinal)
        s += "final ";

    if(allFlags && (flags & Class::AccSuper))
        s += "super ";

    if(allFlags && (flags & Class::AccSynthetic))
        s += "synthetic ";

    if(allFlags && (flags & Class::AccAnnotation))
        s += "annotation ";

    if(flags & Class::AccEnum)
        s += "enum ";
    else if(flags & Class::AccInterface)
        s += "interface ";
    else
        s += "class ";

    // Name
    s += name;

    // Base
    s += " extends " + base;

    // Interfaces
    if(interfaces.size()>0)
    {
        s += " implements ";
        s += strjoin(interfaces.begin(), interfaces.end(), ", ");
    }

    return s;
}
