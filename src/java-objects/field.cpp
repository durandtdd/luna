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

    if(value.isSet)
    {
        str += " = ";
        switch(type.type)
        {
            case Type::Boolean:
                if(type.type == Type::Boolean)
                {
                    if(value.intValue == 0)
                        str += "false";
                    else
                        str += "true";
                }
                break;

            case Type::Byte:
                str += std::to_string((std::int8_t)value.intValue);
                break;

            case Type::Char:
                str += "(char)" + std::to_string((uint16)value.intValue);
                break;

            case Type::Double:
                str += std::to_string(value.doubleValue);
                break;

            case Type::Float:
                str += std::to_string(value.doubleValue);
                break;

            case Type::Int:
                str += std::to_string((std::int32_t)value.intValue);
                break;

            case Type::Long:
                str += std::to_string(value.intValue);
                break;

            case Type::Short:
                str += std::to_string((std::int16_t)value.intValue);
                break;

            default:
                if(value.stringValue != "")
                    str += "\"" + value.stringValue + "\"";
                else
                    str += "null";
                break;
        }
    }

    return str;
}
