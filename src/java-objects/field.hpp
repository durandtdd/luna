#pragma once

#include <string>
#include <vector>

#include "../common.hpp"
#include "type.hpp"
#include "variable.hpp"


struct Field: Variable
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

    /** Field access and property flags */
    uint16 flags = 0;

    /**
     * @brief Construct a Field
     * @param type Field type
     * @param name Field name
     * @param flags Field access and property flags
     */
    Field(Type type = Type(), const std::string& name = "", uint16 flags = 0);

    /**
     * @brief Return a string representation of the field
     * @return String
     */
    std::string str() const;
};
