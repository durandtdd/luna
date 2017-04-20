#include "class.hpp"

#include <algorithm>
#include <sstream>


std::string Class::str() const
{
    std::ostringstream oss;
    oss << name << "\n";

    oss << "    Type:       ";

    if(flags & AccPublic)
        oss << "public ";

    if(flags & AccFinal)
        oss << "final ";

    if(flags & AccSuper)
        oss << "super ";

    if(flags & AccInterface)
        oss << "interface ";

    if(flags & AccAbstract)
        oss << "abstract ";

    if(flags & AccSynthetic)
        oss << "synthetic ";

    if(flags & AccAnnotation)
        oss << "annotation ";

    if(flags & AccEnum)
        oss << "enum ";

    oss << "\n";

    oss << "    Base:       " << base << "\n";

    oss << "    Interfaces: ";
    for(const std::string& interface: interfaces)
        oss << interface << " ";
    oss << "\n";

    oss << "    Fields:\n";
    for(const Field& field: fields)
        oss << "        " << field.str() << "\n";

    oss << "    Methods:\n";
    for(const Method& method: methods)
        oss << "        " << method.str() << "\n";

    return oss.str();
}
