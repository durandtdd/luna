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
 * @brief Compare two constant values
 * @param cv1 Constant value 1
 * @param cv2 Constant value 2
 * @return True if constant values are equal
 */
bool operator==(const ConstantValue& cv1, const ConstantValue& cv2);


/**
 * @brief Compare two constant values
 * @param cv1 Constant value 1
 * @param cv2 Constant value 2
 * @return True if constant values are different
 */
bool operator!=(const ConstantValue& cv1, const ConstantValue& cv2);


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


/**
 * @brief Compare two code attributes
 * @param code1 Code attribute 1
 * @param code2 Code attribute 2
 * @return True if code attributes are equal
 */
bool operator==(const Code& code1, const Code& code2);


/**
 * @brief Compare two code attributes
 * @param code1 Code attribute 1
 * @param code2 Code attribute 2
 * @return True if code attributes are different
 */
bool operator!=(const Code& code1, const Code& code2);


/**
 * @brief Compare two code exceptions
 * @param exception1 Code exception 1
 * @param exception2 Code exception 2
 * @return True if code exceptions are equal
 */
bool operator==(const Code::Exception& code1, const Code::Exception& code2);


/**
 * @brief Compare two code exceptions
 * @param exception1 Code exception 1
 * @param exception2 Code exception 2
 * @return True if code exceptions are different
 */
bool operator!=(const Code::Exception& code1, const Code::Exception& code2);
