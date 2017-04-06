#include "constant-pool-entry.hpp"


ConstantPoolEntry::ConstantPoolEntry(ConstantPoolEntry::Type type):
    m_type(type),
    m_data(0)
{
}


ConstantPoolEntry::Type ConstantPoolEntry::type() const
{
    return m_type;
}


void ConstantPoolEntry::setType(ConstantPoolEntry::Type type)
{
    m_type = type;
}


uint16 ConstantPoolEntry::index1() const
{
    return m_data & 0x000000000000ffff;
}


void ConstantPoolEntry::setIndex1(uint16 index1)
{
    m_data &= 0xffffffffffff0000;
    m_data |= index1;
}


uint16 ConstantPoolEntry::index2() const
{
    return (m_data & 0x00000000ffff0000) >> 16;
}


void ConstantPoolEntry::setIndex2(uint16 index2)
{
    m_data &= 0xffffffff0000ffff;
    m_data |= (index2 << 16);
}


uint64 ConstantPoolEntry::data() const
{
    return m_data;
}

void ConstantPoolEntry::setData(uint64 data)
{
    m_data = data;
}


ConstantPoolEntry::Type ConstantPoolEntry::typeFromInt(uint16 tag)
{
    switch (tag)
    {
    case 1:  return Utf8;
    case 3:  return Integer;
    case 4:  return Float;
    case 5:  return Long;
    case 6:  return Double;
    case 7:  return Class;
    case 8:  return String;
    case 9:  return FieldRef;
    case 10: return MethodRef;
    case 11: return InterfaceMethodRef;
    case 12: return NameAndType;
    case 15: return MethodHandle;
    case 16: return MethodType;
    case 18: return InvokeDynamic;
    default: return Invalid;
    }
}
