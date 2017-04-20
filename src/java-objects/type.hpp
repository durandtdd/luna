#pragma once

#include <string>

#include "../common.hpp"


/**
 * @brief Type of a variable
 */
struct Type
{
    /**
     * @brief Type enum
     */
    enum Enum
    {
        Object,
        Boolean,
        Byte,
        Char,
        Double,
        Float,
        Int,
        Long,
        Short,
        Void
    };

    /** Variable type */
    Enum type = Object;

    /** Object name (only if type == Object) */
    std::string object;

    /** Number of dimnesions (0: Not an array, 1: 1D array...) */
    uint32 dimensions = 0;


    /**
     * @brief Convenience function wchich return a Boolean type
     * @param dims Number of dimensions
     * @return Boolean type
     */
    static Type tBoolean(uint32 dims = 0) {return {Boolean, "", dims};}

    /**
     * @brief Convenience function wchich return a Byte type
     * @param dims Number of dimensions
     * @return Byte type
     */
    static Type tByte(uint32 dims = 0) {return {Byte, "", dims};}

    /**
     * @brief Convenience function wchich return a Char type
     * @param dims Number of dimensions
     * @return Char type
     */
    static Type tChar(uint32 dims = 0) {return {Char, "", dims};}

    /**
     * @brief Convenience function wchich return a Double type
     * @param dims Number of dimensions
     * @return Double type
     */
    static Type tDouble(uint32 dims = 0) {return {Double, "", dims};}

    /**
     * @brief Convenience function wchich return a Float type
     * @param dims Number of dimensions
     * @return Float type
     */
    static Type tFloat(uint32 dims = 0) {return {Float, "", dims};}

    /**
     * @brief Convenience function wchich return an Int type
     * @param dims Number of dimensions
     * @return Int type
     */
    static Type tInt(uint32 dims = 0) {return {Int, "", dims};}

    /**
     * @brief Convenience function wchich return a Long type
     * @param dims Number of dimensions
     * @return Long type
     */
    static Type tLong(uint32 dims = 0) {return {Long, "", dims};}

    /**
     * @brief Convenience function wchich return a Short type
     * @param dims Number of dimensions
     * @return Short type
     */
    static Type tShort(uint32 dims = 0) {return {Short, "", dims};}

    /**
     * @brief Convenience function wchich return a Void type
     * @param dims Number of dimensions
     * @return Void type
     */
    static Type tVoid(uint32 dims = 0) {return {Void, "", dims};}

    /**
     * @brief Convenience function wchich return an Object type
     * @param obj Object name
     * @param dims Number of dimensions
     * @return Object type
     */
    static Type tObject(const std::string& obj, uint32 dims = 0) {return Type{Object, obj, dims};}
};


/**
 * @brief Compare two types
 * @param type1 Type 1
 * @param type2 Type 2
 * @return True if types are equal
 */
bool operator==(const Type& type1, const Type& type2);

/**
 * @brief Compare two types
 * @param type1 Type 1
 * @param type2 Type 2
 * @return True if types are different
 */
bool operator!=(const Type& type1, const Type& type2);
