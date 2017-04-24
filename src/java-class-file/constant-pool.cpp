#include "constant-pool.hpp"

#include <algorithm>
#include <sstream>

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
