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


uint16 ConstantPool::addString(const std::string& str)
{
    m_strings.push_back(str);
    return (uint16) m_strings.size()-1;
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


std::string ConstantPool::getString(uint16 index) const
{
    if(index >= m_entries.size())
        throw ConstantPoolError("Index out of range");

    if(m_entries[index].type() == ConstantPoolEntry::String)
    {
        index = m_entries[index].index1();

        if(index >= m_entries.size())
            throw ConstantPoolError("Index out of range");
    }

    if(m_entries[index].type() != ConstantPoolEntry::Utf8)
        throw ConstantPoolError("ConstantPoolEntry is not UTF8");

    if(m_entries[index].index1() >= m_strings.size())
        throw ConstantPoolError("Invalid string table index");

    return m_strings[m_entries[index].index1()];
}


std::shared_ptr<JavaObjectRef> ConstantPool::getRef(uint16 index) const
{
    // Ref type
    auto cpe = (*this)[index];
    switch(cpe.type())
    {
        case ConstantPoolEntry::FieldRef:
        {
            std::shared_ptr<FieldRef> ref(new FieldRef());

            // Class name
            ref->className = getRef(cpe.index1())->str();
            std::replace(ref->className.begin(), ref->className.end(), '/', '.');

            // Field name
            auto nameAndType = (*this)[cpe.index2()];
            ref->name = getString(nameAndType.index1());

            // Field type
            std::string descriptor = getString(nameAndType.index2());
            ref->type = parseDescriptor(descriptor.begin(), descriptor.end());

            return ref;
        }

        case ConstantPoolEntry::MethodRef:
        case ConstantPoolEntry::InterfaceMethodRef:
        {
            std::shared_ptr<MethodRef> ref(new MethodRef());

            // Class name
            ref->className = getRef(cpe.index1())->str();
            std::replace(ref->className.begin(), ref->className.end(), '/', '.');

            // Field name
            auto nameAndType = (*this)[cpe.index2()];
            ref->name = getString(nameAndType.index1());

            // Field type
            std::string descriptor = getString(nameAndType.index2());
            auto parsed = parseMethodDescriptor(descriptor.begin(), descriptor.end());
            ref->type = parsed.type;
            ref->parameters = parsed.parameters;
            return ref;
        }

        case ConstantPoolEntry::Class:
        {
            std::shared_ptr<ClassRef> ref(new ClassRef());

            // Class name
            std::string s = getString(cpe.index1());
            if(s.size()>1 && (s.front() == '[' || s.back() == ';'))
                ref->className = parseDescriptor(s.begin(), s.end()).str();
            else
            {
                ref->className = s;
                std::replace(ref->className.begin(), ref->className.end(), '/', '.');
            }

            return ref;
        }

        default:
            throw ConstantPoolError("Entry is not a reference");
    }
}


int64 ConstantPool::getInt(uint16 index) const
{
    auto cpe = (*this)[index];

    switch(cpe.type())
    {
        case ConstantPoolEntry::Integer:
            return (int32)cpe.data();

        case ConstantPoolEntry::Long:
            return (int64)cpe.data();

        default:
            throw ConstantPoolError("Entry is not an integer");
    }
}


double ConstantPool::getDouble(uint16 index) const
{
    auto cpe = (*this)[index];

    switch(cpe.type())
    {
        case ConstantPoolEntry::Float:
        {
            uint32 d = (uint32)cpe.data();
            return *reinterpret_cast<float*>(&d);
        }

        case ConstantPoolEntry::Double:
        {
            uint64 d = cpe.data();
            return *reinterpret_cast<double*>(&d);
        }

        default:
            throw ConstantPoolError("Entry is not float");
    }
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
                oss << "[UTF8] " << getString(k);
                break;

            case ConstantPoolEntry::Integer:
                oss << "[Integer] ";
                oss << "Value = " << getInt(k);
                break;

            case ConstantPoolEntry::Float:
                oss << "[Float] ";
                oss << "Value = " << getDouble(k);
                break;

            case ConstantPoolEntry::Long:
                oss << "[Long] ";
                oss << "Value = " << getInt(k);
                break;

            case ConstantPoolEntry::Double:
                oss << "[Double] ";
                oss << "Value = " << getDouble(k);
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
