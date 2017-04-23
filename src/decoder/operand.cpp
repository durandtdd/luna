#include "operand.hpp"


Operand::Operand(Type type, uint32 data):
    m_data(data),
    m_type(type)
{
}


int64 Operand::get() const
{
    switch(m_type)
    {
        case Operand::INT8:
            return to<int8>();

        case Operand::UINT8:
            return to<uint8>();

        case Operand::INT16:
            return to<int16>();

        case Operand::UINT16:
            return to<uint16>();

        case Operand::INT32:
            return to<int32>();

        case Operand::UINT32:
            return to<uint32>();

        default:
            return 0;
    }
}


Operand::Type Operand::type() const
{
    return m_type;
}


void Operand::setType(const Type& type)
{
    m_type = type;
}
