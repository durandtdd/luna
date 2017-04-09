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
