#pragma once

#include <string>

#include "type.hpp"


/**
 * @brief Struct representing a variable
 */
struct Variable
{
    /** Variable type */
    Type type;

    /** Variable name */
    std::string name;

    /**
     * @brief Construct a Variable
     * @param type Type
     * @param name Name
     */
    Variable(Type type = Type(), const std::string& name = "");

    /**
     * @brief Return a string representation of the variable
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
