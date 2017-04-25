#pragma once

#include <string>
#include <vector>

#include "../common.hpp"
#include "attribute.hpp"
#include "type.hpp"
#include "variable.hpp"


struct Field
{
public:
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


public:
    /** Field type */
    Type type;

    /** Field name */
    std::string name;

    /** Field access and property flags */
    uint16 flags = 0;

    /** Initial value */
    ConstantValue value;


public:
    /**
     * @brief Convert field to a string representation
     * @param allFlags If set to false, only print flags appearing in java code (public, static, final...)
     * @return String
     */
    std::string str(bool allFlags = false) const;
};
