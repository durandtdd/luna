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
