#pragma once

#include <string>
#include <vector>

#include "../common.hpp"
#include "../constant-pool.hpp"
#include "../streamreader.hpp"


/**
 * @brief Error thrown by attributes
 */
class AttributeError: public Error
{
    using Error::Error;
};


/**
 * @brief Base abstract class for all attributes
 */
struct Attribute
{
public:
    /**
     * @brief Supported attributes
     */
    enum Type
    {
        ConstantValue,
        Code,
        Unknown
    };


public:
    /** Type */
    Type type = Unknown;

    /** Flag indicating that the attribute is set in the file */
    bool isSet = false;


public:
    /** Destructor */
    virtual ~Attribute() {}
};



/**
 * @brief A ContantValue
 */
struct ConstantValue: public Attribute
{
public:
    /** Integer value (only for int types) */
    std::int64_t intValue = 0;

    /** Double value (only for float types) */
    double doubleValue = 0;

    /** String value (only for string types) */
    std::string stringValue;

public:
    /**
     * @brief Construct a ConstantValue
     */
    ConstantValue() {type = Attribute::ConstantValue;}
};



/**
 * @brief A Code attribute
 */
struct Code: public Attribute
{
public:
    /**
     * @brief An exception in the exception table
     */
    struct Exception
    {
        /** Start of the exception handler */
        uint16 start = 0;

        /** End of the exception handler */
        uint16 end = 0;

        /** Start of the handler */
        uint16 handler = 0;

        /** Catch type */
        std::string type;
    };


public:
    /** Code */
    std::vector<uint8> code;

    /** Exceptions */
    std::vector<Exception> exceptions;


public:
    /**
     * @brief Construct a Code
     */
    Code() {type = Attribute::Code;}
};

