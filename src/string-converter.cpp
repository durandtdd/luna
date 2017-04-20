#include "string-converter.hpp"

#include <iomanip>
#include <sstream>


std::string StringConverter::str(const Type& type)
{
    std::ostringstream oss;

    switch(type.type)
    {
        case Type::Object:  oss << type.object; break;
        case Type::Boolean: oss << "boolean"; break;
        case Type::Byte:    oss << "byte"; break;
        case Type::Char:    oss << "char"; break;
        case Type::Double:  oss << "double"; break;
        case Type::Float:   oss << "float"; break;
        case Type::Int:     oss << "int"; break;
        case Type::Long:    oss << "long"; break;
        case Type::Short:   oss << "short"; break;
        case Type::Void:    oss << "void"; break;
    }

    for(uint32 k=0; k<type.dimensions; k++)
        oss << "[]";

    return oss.str();
}


std::string StringConverter::str(const Variable& variable)
{
    return str(variable.type) + " " + variable.name;
}


std::string StringConverter::str(const Field& field, bool allFlags)
{
    std::ostringstream oss;

    if(field.flags & Field::AccPublic)
        oss << "public ";

    if(field.flags & Field::AccPrivate)
        oss << "private ";

    if(field.flags & Field::AccProtected)
        oss << "protected ";

    if(field.flags & Field::AccStatic)
        oss << "static ";

    if(field.flags & Field::AccFinal)
        oss << "final ";

    if(field.flags & Field::AccVolatile)
        oss << "volatile ";

    if(field.flags & Field::AccTransient)
        oss << "transient ";

    if(allFlags && (field.flags & Field::AccSynthetic))
        oss << "synthetic ";

    if(allFlags && (field.flags & Field::AccEnum))
        oss << "enum ";

    oss << str(field.type)  << " " << field.name;

    if(field.value.isSet)
    {
        oss << " = ";
        switch(field.type.type)
        {
            case Type::Boolean:
                if(field.value.intValue == 0)
                    oss << "false";
                else
                    oss << "true";
                break;

            case Type::Byte:
                oss << std::to_string((std::int8_t)field.value.intValue);
                break;

            case Type::Char:
                oss << "(char)" + std::to_string((uint16)field.value.intValue);
                break;

            case Type::Double:
                oss << std::to_string(field.value.doubleValue);
                break;

            case Type::Float:
                oss << std::to_string(field.value.doubleValue);
                break;

            case Type::Int:
                oss << std::to_string((std::int32_t)field.value.intValue);
                break;

            case Type::Long:
                oss << std::to_string(field.value.intValue);
                break;

            case Type::Short:
                oss << std::to_string((std::int16_t)field.value.intValue);
                break;

            default:
                if(field.value.stringValue != "")
                    oss << "\"" + field.value.stringValue + "\"";
                else
                    oss << "null";
                break;
        }
    }

    return oss.str();
}


std::string StringConverter::str(const Method& method, bool allFlags)
{
    std::ostringstream oss;

    if(method.flags & Method::AccPublic)
        oss << "public ";

    if(method.flags & Method::AccPrivate)
        oss << "private ";

    if(method.flags & Method::AccProtected)
        oss << "protected ";

    if(method.flags & Method::AccStatic)
        oss << "static ";

    if(method.flags & Method::AccFinal)
        oss << "final ";

    if(method.flags & Method::AccSynchronized)
        oss << "synchronized ";

    if(method.flags & Method::AccBridge)
        oss << "bridge ";

    if(allFlags && (method.flags & Method::AccVarArgs))
        oss << "varargs ";

    if(method.flags & Method::AccNative)
        oss << "native ";

    if(method.flags & Method::AccAbstract)
        oss << "abstract ";

    if(allFlags && (method.flags & Method::AccStrict))
        oss << "strict ";

    if(allFlags && (method.flags & Method::AccSynthetic))
        oss << "synthetic ";

    oss << str(method.type) << " " << method.name;

    oss << "(";
    for(auto it = method.parameters.begin(); it!=method.parameters.end(); ++it)
    {
        oss << str(*it);
        if(it != method.parameters.end()-1)
            oss << ", ";
    }
    oss << ")";

    return oss.str();
}


std::string StringConverter::str(const Class& cl, bool allFlags)
{
    std::ostringstream oss;


    if(cl.flags & Class::AccEnum)
        oss << "enum ";

    if(cl.flags & Class::AccPublic)
        oss << "public ";

    if(cl.flags & Class::AccAbstract)
        oss << "abstract ";

    if(cl.flags & Class::AccFinal)
        oss << "final ";

    if(allFlags && (cl.flags & Class::AccSuper))
        oss << "super ";

    if(allFlags && (cl.flags & Class::AccSynthetic))
        oss << "synthetic ";

    if(allFlags && (cl.flags & Class::AccAnnotation))
        oss << "annotation ";

    if(cl.flags & Class::AccEnum)
        oss << "enum ";
    else if(cl.flags & Class::AccInterface)
        oss << "interface ";
    else
        oss << "class ";

    oss << cl.name;

    oss << " extends " << cl.base;

    if(cl.interfaces.size()>0)
    {
        oss << " implements ";
        for(auto it = cl.interfaces.begin(); it!=cl.interfaces.end(); ++it)
        {
            oss << *it;
            if(it != cl.interfaces.end()-1)
                oss << ", ";
        }
    }

    return oss.str();
}


std::string StringConverter::str(const ConstantPool& cp)
{
    std::ostringstream oss;

    for(std::size_t k=0; k<cp.size(); k++)
    {
        oss << "[" << std::setw(4) << std::setfill('0') << k << "] ";
        oss << std::setw(0);

        switch(cp[k].type())
        {
            case ConstantPoolEntry::Utf8:
                oss << "[UTF8] " << cp.string(k);
                break;

            case ConstantPoolEntry::Integer:
                oss << "[Integer] ";
                oss << "Value = " << cp[k].data();
                break;

            case ConstantPoolEntry::Float:
            {
                oss << "[Float] ";
                uint64 v = cp[k].data();
                oss << "Value = " << *reinterpret_cast<float*>(&v);
                break;
            }

            case ConstantPoolEntry::Long:
                oss << "[Long] ";
                oss << "Value = " << cp[k].data();
                break;

            case ConstantPoolEntry::Double:
            {
                oss << "[Double] ";
                uint64 v = cp[k].data();
                oss << "Value = " << *reinterpret_cast<double*>(&v);
                break;
            }

            case ConstantPoolEntry::Class:
                oss << "[Class] ";
                oss << "Name = " << cp[k].index1();
                break;

            case ConstantPoolEntry::String:
                oss << "[String] ";
                oss << "Value = " << cp[k].index1();
                break;

            case ConstantPoolEntry::FieldRef:
                oss << "[FieldRef] ";
                oss << "Class = " << cp[k].index1() << "; ";
                oss << "NameAndType = " << cp[k].index2();
                break;

            case ConstantPoolEntry::MethodRef:
                oss << "[MethodRef] ";
                oss << "Class = " << cp[k].index1() << "; ";
                oss << "NameAndType = " << cp[k].index2();
                break;

            case ConstantPoolEntry::InterfaceMethodRef:
                oss << "[InterfaceMethodRef] ";
                oss << "Class = " << cp[k].index1() << "; ";
                oss << "NameAndType = " << cp[k].index2();
                break;

            case ConstantPoolEntry::NameAndType:
                oss << "[NameAndType] ";
                oss << "Name = " << cp[k].index1() << "; ";
                oss << "Type = " << cp[k].index2();
                break;

            case ConstantPoolEntry::MethodHandle:
                oss << "[MethodHandle] ";
                oss << "Reference kind = " << cp[k].index1() << "; ";
                oss << "Reference index = " << cp[k].index2();
                break;

            case ConstantPoolEntry::MethodType:
                oss << "[MethodType] ";
                oss << "Type = " << cp[k].index1();
                break;

            case ConstantPoolEntry::InvokeDynamic:
                oss << "[InvokeDynamic] ";
                oss << "Bootstrap = " << cp[k].index1() << "; ";
                oss << "NameAndType = " << cp[k].index2();
                break;

            case ConstantPoolEntry::Invalid:
                oss << "[Invalid]";
                break;
        }

        oss << "\n";
    }

    return oss.str();
}


std::string StringConverter::str(const Instruction& instruction)
{
    std::ostringstream oss;

    oss << "/* " << std::setw(4) << std::setfill('0') << instruction.offset << " */ ";
    oss << std::setw(0);

    oss << mnemonicStr(instruction.mnemonic);


    if(instruction.operands.size() > 0)
    {
        oss << " ";
        for(auto it = instruction.operands.begin(); it != instruction.operands.end(); ++it)
        {
            oss << it->get();

            if(it != instruction.operands.end()-1)
                oss << ", ";
        }
    }

    return oss.str();
}
