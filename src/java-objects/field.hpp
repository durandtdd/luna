#pragma once

#include <string>
#include <vector>

#include "../common.hpp"
#include "type.hpp"
#include "variable.hpp"


struct Field
{
    /**
     * @brief Field access and property flags
     */
    enum Flags
    {
        AccPublic = 0x0001,
        AccPrivate = 0x0002,
        AccProtected = 0x0004,
        AccStatic = 0x0008,
        AccFinal = 0x0010,
        AccVolatile = 0x0040,
        AccTransient = 0x0080,
        AccSynthetic = 0x1000,
        AccEnum = 0x4000
    };

    /** Field type */
    Type type;

    /** Field name */
    std::string name;

    /** Field access and property flags */
    uint16 flags = 0;


    /**
     * @brief Return a string representation of the field
     * @return String
     */
    std::string str() const;
};


/**
 * @brief Compare two fields
 * @param field1 Field 1
 * @param field2 Field 2
 * @return True if fields are equal
 */
bool operator==(const Field& field1, const Field& field2);


/**
 * @brief Compare two fields
 * @param field1 Field 1
 * @param field2 Field 2
 * @return True if fields are different
 */
bool operator!=(const Field& field1, const Field& field2);
