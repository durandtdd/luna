#pragma once

#include <string>

#include "type.hpp"


/**
 * @brief Struct representing a variable
 */
struct Variable
{
public:
    /** Variable type */
    Type type;

    /** Variable name */
    std::string name;


public:
    /**
     * @brief Convert variable to a string representation
     * @return String
     */
    std::string str() const;
};


/**
 * @brief Compare two variables
 * @param var1 Variable 1
 * @param var2 Variable 2
 * @return True if variables are equal
 */
bool operator==(const Variable& var1, const Variable& var2);


/**
 * @brief Compare two variables
 * @param var1 Variable 1
 * @param var2 Variable 2
 * @return True if variables are different
 */
bool operator!=(const Variable& var1, const Variable& var2);
