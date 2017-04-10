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
    uint32 dimensions;


    /**
     * @brief Construct a Type
     * @param type Type
     * @param object Object name (only if type == Object)
     * @param dimensions Number of dimnesions (0: Not an array, 1: 1D array...)
     */
    Type(Enum type = Object, const std::string& object = "", uint32 dimensions = 0);


    /**
     * @brief Convert to a string
     * @return String
     */
    std::string str() const;
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
