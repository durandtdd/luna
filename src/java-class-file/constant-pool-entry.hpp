#pragma once

#include <string>
#include <vector>

#include "../common.hpp"



/**
 * @brief Class representing an entry in the constant pool
 *
 * Each type must only use the methods defined in the table below
 * Calling another method is undetermined
 *
 * +--------------------+-------------+-------------+--------+
 * | Entry type         |   Index 1   |   Index 2   |  Data  |
 * +--------------------+-------------+-------------+--------+
 * | Class              | Name        |             |        |
 * | FieldRef           | Class       | NameAndType |        |
 * | MethodRef          | Class       | NameAndType |        |
 * | InterfaceMethodRef | Class       | NameAndType |        |
 * | String             | Index (ST)  |             |        |
 * | Integer            |             |             | Value  |
 * | Float              |             |             | Value  |
 * | Long               |             |             | Value  |
 * | Double             |             |             | Value  |
 * | NameAndType        | Name        | Descriptor  |        |
 * | Utf8               | Index (ST)  |             |        |
 * | MethodHandle       | Ref kind    | Ref index   |        |
 * | MethodType         | Descriptor  |             |        |
 * | InvokeDynamic      | Bootstrap   | NameAndType |        |
 * +--------------------+-------------+-------------+--------+
 * ST = String Table
 */
class ConstantPoolEntry
{
public:
    /**
     * @brief Entry types
     */
    enum Type
    {
        Utf8 ,
        Integer,
        Float,
        Long,
        Double,
        Class,
        String,
        FieldRef,
        MethodRef,
        InterfaceMethodRef,
        NameAndType,
        MethodHandle,
        MethodType,
        InvokeDynamic,
        Invalid
    };


public:
    /**
     * @brief Construct a ConstantPoolEntry with data
     * @param type Entry type
     * @param data Data
     */
    ConstantPoolEntry(Type type = Invalid, uint64 data = 0);

    /**
     * @brief Construct a ConstantPoolEntry with indices
     * @param type Entry type
     * @param index1 Index 1
     * @param index2 Index 2
     */
    ConstantPoolEntry(Type type, uint16 index1, uint16 index2);

    /**
     * @brief Get entry type
     * @return Type
     */
    Type type() const;

    /**
     * @brief Set entry type
     * @param type Entry type
     */
    void setType(Type type);

    /**
     * @brief Get index 1 value
     * @return Value
     */
    uint16 index1() const;

    /**
     * @brief Set index 1 value
     * @param index1 Value
     */
    void setIndex1(uint16 index1);

    /**
     * @brief Get index 2 value
     * @return Value
     */
    uint16 index2() const;

    /**
     * @brief Set index 2 value
     * @param index2 Value
     */
    void setIndex2(uint16 index2);

    /**
     * @brief Get data value
     * @return Value
     */
    uint64 data() const;

    /**
     * @brief Set data value
     * @param data Value
     */
    void setData(uint64 data);


public:
    /**
     * @brief Get entry type from an integer tag
     * @param tag Integer
     * @return Type
     */
    static Type typeFromInt(uint16 tag);


private:
    /** Entry type */
    Type m_type;

    /** Data or indices */
    uint64 m_data;
};


