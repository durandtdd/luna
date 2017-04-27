#pragma once

#include <string>
#include <vector>

#include "../common.hpp"
#include "../java-objects/type.hpp"
#include "../java-objects/variable.hpp"


/**
 * @brief Base class for all ref
 */
struct JavaObjectRef
{
public:
    /**
     * @brief Ref type
     */
    enum RefType
    {
        Field,
        Method,
        Class
    };


public:
    /** Reference type */
    RefType refType;


public:
    /**
     * @brief Convert ref to a string representation
     * @return String
     */
    virtual std::string str() const = 0;
};


/**
 * @brief A field reference
 */
struct FieldRef: public JavaObjectRef
{
public:
    /** Field type */
    Type type;

    /** Class name */
    std::string className;

    /** Field name */
    std::string name;


public:
    /**
     * @brief Construct a FieldRef
     */
    FieldRef();

    /**
     * @see JavaObjectRef::str
     */
    std::string str() const override;
};


/**
 * @brief A method reference
 */
struct MethodRef: public JavaObjectRef
{
public:
    /** Method return type */
    Type type;

    /** Class name */
    std::string className;

    /** Method name */
    std::string name;

    /** Parameters */
    std::vector<Variable> parameters;


public:
    /**
     * @brief Construct a MethodRef
     */
    MethodRef();

    /**
     * @see JavaObjectRef::str
     */
    std::string str() const override;
};


/**
 * @brief A class reference
 */
struct ClassRef: public JavaObjectRef
{
public:
    /** Class name */
    std::string className;

public:
    /**
     * @brief Construct a ClassRef
     */
    ClassRef();

    /**
     * @see JavaObjectRef::str
     */
    std::string str() const override;
};
