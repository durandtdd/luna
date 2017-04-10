#pragma once

#include <string>

#include "field.hpp"
#include "method.hpp"


struct Class
{
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
    uint16 flags;


    /**
     * @brief Return a string representation of the class
     * @return String
     */
    std::string str() const;
};


/**
 * @brief Compare two classes
 * @param class1 Class 1
 * @param class2 Class 2
 * @return True if classes are equal
 */
bool operator==(const Class& class1, const Class& class2);


/**
 * @brief Compare two classes
 * @param class1 Class 1
 * @param class2 Class 2
 * @return True if classes are different
 */
bool operator!=(const Class& class1, const Class& class2);
