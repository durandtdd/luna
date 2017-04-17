#include "constant-pool-entry.hpp"

#include <iomanip>
#include <sstream>


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


std::string ConstantPoolEntry::str() const
{
    std::ostringstream oss;

    switch(m_type)
    {
        case ConstantPoolEntry::Utf8:
            oss << "Utf8 [Index=" << index1() << "]";
            break;

        case ConstantPoolEntry::Integer:
            oss << "Integer [Value=" << m_data<< "]";
            break;

        case ConstantPoolEntry::Float:
        {
            uint32 d = (uint32)m_data;
            oss << "Float [Value=" << *reinterpret_cast<float*>(&d) << "]";
            break;
        }

        case ConstantPoolEntry::Long:
            oss << "Integer [Value=" << m_data << "]";
            break;

        case ConstantPoolEntry::Double:
        {
            uint64 d = m_data;
            oss << "Float [Value=" << *reinterpret_cast<double*>(&d) << "]";
            break;
        }

        case ConstantPoolEntry::Class:
            oss << "Class [NameIndex=" << index1() << "]";
            break;

        case ConstantPoolEntry::String:
            oss << "String [Index=" << index1() << "]";
            break;

        case ConstantPoolEntry::FieldRef:
            oss << "FieldRef [ClassIndex=" << index1() << ", NameAndTypeIndex=" << index2() << "]";
            break;

        case ConstantPoolEntry::MethodRef:
            oss << "MethodRef [ClassIndex=" << index1() << ", NameAndTypeIndex=" << index2() << "]";
            break;

        case ConstantPoolEntry::InterfaceMethodRef:
            oss << "InterfaceMethodRef [ClassIndex=" << index1() << ", NameAndTypeIndex=" << index2() << "]";
            break;

        case ConstantPoolEntry::NameAndType:
            oss << "NameAndType [NameIndex=" << index1() << ", DescriptorIndex=" << index2() << "]";
            break;

        case ConstantPoolEntry::MethodHandle:
            oss << "MethodHandle [RefKind=" << index1() << ", RefIndex=" << index2() << "]";
            break;

        case ConstantPoolEntry::MethodType:
            oss << "MethodType [Bootstrap=" << index1() << ", NameAndTypeIndex=" << index2() << "]";
            break;

        case ConstantPoolEntry::InvokeDynamic:
            oss << "InvokeDynamic [Descriptor=" << index1() << "]";
            break;

        case ConstantPoolEntry::Invalid:
            oss << "Invalid []";
            break;
    }

    return oss.str();
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
