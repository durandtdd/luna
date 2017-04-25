#include "field.hpp"


std::string Field::str(bool allFlags) const
{
    std::string s;

    // Flags
    if(flags & Field::AccPublic)
        s += "public ";

    if(flags & Field::AccPrivate)
        s += "private ";

    if(flags & Field::AccProtected)
        s += "protected ";

    if(flags & Field::AccStatic)
        s += "static ";

    if(flags & Field::AccFinal)
        s += "final ";

    if(flags & Field::AccVolatile)
        s += "volatile ";

    if(flags & Field::AccTransient)
        s += "transient ";

    if(allFlags && (flags & Field::AccSynthetic))
        s += "synthetic ";

    if(allFlags && (flags & Field::AccEnum))
        s += "enum ";

    // Type and name
    s += type.str();
    s += " ";
    s += name;

    // Initial value
    if(value.isSet)
    {
        s += " = ";
        switch(type.type)
        {
            case Type::Boolean:
                if(value.intValue == 0)
                    s += "false";
                else
                    s += "true";
                break;

            case Type::Byte:
                s += std::to_string((std::int8_t)value.intValue);
                break;

            case Type::Char:
                s += "(char)" + std::to_string((uint16)value.intValue);
                break;

            case Type::Double:
                s += std::to_string(value.doubleValue);
                break;

            case Type::Float:
                s += std::to_string(value.doubleValue);
                break;

            case Type::Int:
                s += std::to_string((std::int32_t)value.intValue);
                break;

            case Type::Long:
                s += std::to_string(value.intValue);
                break;

            case Type::Short:
                s += std::to_string((std::int16_t)value.intValue);
                break;

            default:
                if(value.stringValue != "")
                    s += "\"" + value.stringValue + "\"";
                else
                    s += "null";
                break;
        }
    }

    return s;
}
