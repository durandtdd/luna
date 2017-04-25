#pragma once

#include <string>

#include "field.hpp"
#include "method.hpp"


struct Class
{
public:
    /**
     * @brief Class access and property flags
     */
    enum Flags
    {
        AccPublic = 0x0001,
        AccFinal = 0x0010,
        AccSuper = 0x0020,
        AccInterface = 0x0200,
        AccAbstract = 0x0400,
        AccSynthetic = 0x1000,
        AccAnnotation = 0x2000,
        AccEnum = 0x4000
    };


public:
    /** Class name */
    std::string name;

    /** Base class name */
    std::string base;

    /** Directly implemented interfaces */
    std::vector<std::string> interfaces;

    /** Fields */
    std::vector<Field> fields;

    /** Methods */
    std::vector<Method> methods;

    /** Flags */
    uint16 flags = 0;


public:
    /**
     * @brief Convert class to a string representation
     * @param allFlags If set to false, only print flags appearing in java code (public, final...)
     * @return String
     */
    std::string str(bool allFlags = false) const;
};
