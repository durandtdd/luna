#include "class.hpp"

#include <sstream>


std::string Class::str() const
{
    std::ostringstream oss;
    oss << name << "\n";

    oss << "    Type:       ";
    if(flags & AccInterface)
        oss << "interface";
    else
        oss << "class";
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
