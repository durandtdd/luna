#pragma once

#include "../common.hpp"


/**
 * @brief Class holding information of a decoded operand (type, value)
 *
 * Operand value can be accessed with methods to() or get()
 *
 * Operand operand(Operand::UINT16);
 * operand.from<uint16>(0xffff);
 * operand.to<uint16>(); // == 65535
 * operand.to<int16>();  // == -1
 * operand.get();        // == 65535
 */
class Operand
{
public:
    /**
     * @brief Operand types
     */
    enum Type
    {
        INT8, UINT8,
        INT16, UINT16,
        INT32, UINT32,
        DUMMY, VAR
    };


public:
    /**
     * @brief Construct an operand
     * @param type Type
     * @param data Value
     */
    Operand(Type type = UINT32, uint32 data = 0);

    /**
     * @brief Set operand value from type
     * @param value New value
     */
    template<typename T>
    void from(T value);

    /**
     * @brief Convert operand value to type
     * @return Converted value
     */
    template<typename T>
    T to() const;

    /**
     * @brief Get value converted to current operand type
     * @return Converted value
     *
     * If current type is DUMMY or VAR, 0 is returned
     */
    int64 get() const;

    /**
     * @brief Get operand type
     * @return Type
     */
    Type type() const;

    /**
     * @brief Set operand type
     * @param value Type
     */
    void setType(const Type& type);


private:
    /** Data */
    uint32 m_data;

    /** Type */
    Type m_type;
};





template<typename T>
void Operand::from(T value)
{
    m_data = (uint32)value;
}


template<typename T>
T Operand::to() const
{
    static uint32 mask = ((uint64)1 << 8*sizeof(T))-1;
    return (T)(m_data & mask);
}
