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


bool operator==(const Class& class1, const Class& class2)
{
    return (class1.name == class2.name) &&

            (class1.base == class2.base) &&

            (class1.flags == class2.flags) &&

            (class1.interfaces.size() == class2.interfaces.size()) &&
            std::equal(class1.interfaces.begin(), class1.interfaces.end(), class2.interfaces.begin()) &&

            (class1.fields.size() == class2.fields.size()) &&
            std::equal(class1.fields.begin(), class1.fields.end(), class2.fields.begin()) &&

            (class1.methods.size() == class2.methods.size()) &&
            std::equal(class1.methods.begin(), class1.methods.end(), class2.methods.begin());
}


bool operator!=(const Class& class1, const Class& class2)
{
    return !(class1 == class2);
}
