#include "constant-pool.hpp"

#include <algorithm>
#include <iomanip>
#include <sstream>

#include "../utils.hpp"
#include "descriptor-parser.hpp"


void ConstantPool::addEntry(const ConstantPoolEntry& cpe)
{
    m_entries.push_back(cpe);
}


void ConstantPool::addString(const std::string& str)
{
    m_strings.push_back(str);
}


std::string ConstantPool::string(uint16 index) const
{
    if(index >= m_entries.size())
        throw ConstantPoolError("Index out of range");

    if(m_entries[index].type() != ConstantPoolEntry::Utf8)
        throw ConstantPoolError("ConstantPoolEntry is not UTF8");

    if(m_entries[index].index1() >= m_strings.size())
        throw ConstantPoolError("Invalid string table index");

    return m_strings[m_entries[index].index1()];
}


const ConstantPoolEntry& ConstantPool::operator[](uint16 index) const
{
    if(index >= m_entries.size())
        throw ConstantPoolError("Index out of range");

    return m_entries[index];
}


ConstantPoolEntry& ConstantPool::operator[](uint16 index)
{
    if(index >= m_entries.size())
        throw ConstantPoolError("Index out of range");

    return m_entries[index];
}


size_t ConstantPool::size() const
{
    return m_entries.size();
}


size_t ConstantPool::stringsSize() const
{
    return m_strings.size();
}


JavaObjectRef ConstantPool::getRef(uint16 index) const
{
    JavaObjectRef ref;

    // Ref type
    auto cpe = (*this)[index];
    switch(cpe.type())
    {
        case ConstantPoolEntry::FieldRef:
            ref.refType = JavaObjectRef::Field;
            break;

        case ConstantPoolEntry::MethodRef:
            ref.refType = JavaObjectRef::Method;
            break;

        case ConstantPoolEntry::InterfaceMethodRef:
            ref.refType = JavaObjectRef::InterfaceMethod;
            break;

        default:
            throw ConstantPoolError("Entry is not a reference");
    }

    // Class name
    ref.className = string((*this)[cpe.index1()].index1());
    std::replace(ref.className.begin(), ref.className.end(), '/', '.');

    // Ref name
    auto nameAndType = (*this)[cpe.index2()];
    ref.name = string(nameAndType.index1());

    // Ref type
    std::string descriptor = string(nameAndType.index2());
    auto it = descriptor.begin();

    if(ref.refType == JavaObjectRef::Field)
        ref.type = parseDescriptor(it, descriptor.end());
    else
    {
        auto parsed = parseMethodDescriptor(it, descriptor.end());
        ref.type = parsed.type;
        ref.parameters = parsed.parameters;
    }

    return ref;
}


std::string ConstantPool::str() const
{
    std::ostringstream oss;

    for(std::size_t k=0; k<m_entries.size(); k++)
    {
        // Index
        oss << "[" << std::setw(4) << std::setfill('0') << k << "] " << std::setw(0);

        // Value
        switch(m_entries[k].type())
        {
            case ConstantPoolEntry::Utf8:
                oss << "[UTF8] " << string(k);
                break;

            case ConstantPoolEntry::Integer:
                oss << "[Integer] ";
                oss << "Value = " << m_entries[k].data();
                break;

            case ConstantPoolEntry::Float:
                oss << "[Float] ";
                oss << "Value = " << bytesToFloat(m_entries[k].data());
                break;

            case ConstantPoolEntry::Long:
                oss << "[Long] ";
                oss << "Value = " << m_entries[k].data();
                break;

            case ConstantPoolEntry::Double:
                oss << "[Double] ";
                oss << "Value = " << bytesToDouble(m_entries[k].data());
                break;

            case ConstantPoolEntry::Class:
                oss << "[Class] ";
                oss << "Name = " << m_entries[k].index1();
                break;

            case ConstantPoolEntry::String:
                oss << "[String] ";
                oss << "Value = " << m_entries[k].index1();
                break;

            case ConstantPoolEntry::FieldRef:
                oss << "[FieldRef] ";
                oss << "Class = " << m_entries[k].index1() << "; ";
                oss << "NameAndType = " << m_entries[k].index2();
                break;

            case ConstantPoolEntry::MethodRef:
                oss << "[MethodRef] ";
                oss << "Class = " << m_entries[k].index1() << "; ";
                oss << "NameAndType = " << m_entries[k].index2();
                break;

            case ConstantPoolEntry::InterfaceMethodRef:
                oss << "[InterfaceMethodRef] ";
                oss << "Class = " << m_entries[k].index1() << "; ";
                oss << "NameAndType = " << m_entries[k].index2();
                break;

            case ConstantPoolEntry::NameAndType:
                oss << "[NameAndType] ";
                oss << "Name = " << m_entries[k].index1() << "; ";
                oss << "Type = " << m_entries[k].index2();
                break;

            case ConstantPoolEntry::MethodHandle:
                oss << "[MethodHandle] ";
                oss << "Reference kind = " << m_entries[k].index1() << "; ";
                oss << "Reference index = " << m_entries[k].index2();
                break;

            case ConstantPoolEntry::MethodType:
                oss << "[MethodType] ";
                oss << "Type = " << m_entries[k].index1();
                break;

            case ConstantPoolEntry::InvokeDynamic:
                oss << "[InvokeDynamic] ";
                oss << "Bootstrap = " << m_entries[k].index1() << "; ";
                oss << "NameAndType = " << m_entries[k].index2();
                break;

            case ConstantPoolEntry::Invalid:
                oss << "[Invalid]";
                break;
        }

        oss << "\n";
    }

    return oss.str();
}


std::string JavaObjectRef::str() const
{
    std::string s;

    // Type
    s += type.str();
    s += " ";

    // Class
    s += className;
    s += ".";

    // Name
    s += name;

    // Parameters
    if(refType != JavaObjectRef::Field)
    {
        s += "(";
        s += strjoin(parameters.begin(), parameters.end(), ", ", [](auto e) {return e.str();});
        s += ")";
    }

    return s;
}
