#pragma once

#include <string>
#include <vector>

#include "type.hpp"
#include "variable.hpp"


struct Method
{
    enum Flags
    {
        AccPublic = 0x0001,
        AccPrivate = 0x0002,
        AccProtected = 0x0004,
        AccStatic = 0x0008,
        AccFinal = 0x0010,
        AccSynchronized = 0x0020,
        AccBridge = 0x0040,
        AccVarArgs = 0x0080,
        AccNative = 0x0100,
        AccAbstract = 0x0400,
        AccStrict = 0x0800,
        AccSynthetic = 0x1000
    };

    /** Method type */
    Type type;

    /** Method name */
    std::string name;

    /** Parameters */
    std::vector<Variable> parameters;

    /** Method access and property flags */
    uint16 flags = 0;

    /**
     * @brief Construct a Method
     * @param name Method name
     * @param type Method type
     * @param flags Method access and property flags
     */
    Method(const std::string& name = "", Type type = Type(), uint16 flags = 0);

    /**
     * @brief Return a string representation of the method
     * @return String
     */
    std::string str() const;
};


/**
 * @brief Compare two methods
 * @param method1 Method 1
 * @param method2 Method 2
 * @return True if methods are equal
 */
bool operator==(const Method& method1, const Method& method2);


/**
 * @brief Compare two methods
 * @param method1 Method 1
 * @param method2 Method 2
 * @return True if methods are different
 */
bool operator!=(const Method& method1, const Method& method2);
